#include "defs.h"

static void fill_preview_cmd(char* preview, struct options *options);
static void fill_reload_cmd(char* reload, char** argv);
static int fzf_fork(int fd_fr, struct options *options, char** argv);
static int query_fork(char *filepath, ssize_t len_filepath);
static void exec_query(char* query, char* filepath);

#define push_column_id(cur) (cur = (char*)memcpy(cur, (options->hide_date ? "{1}" : "{2}"), 3) + 3)
#define push_cur(cur, cstr) (cur = (char*)memcpy(cur, cstr, sizeof(cstr) - 1) + sizeof(cstr) - 1)
#define push_str(cur, str)  do { size_t len = strlen(str); memcpy(cur, str, len); cur += len; } while(0)

void launch_in_fzf(struct options *options, char** argv)
{
  int pipe_fr[2];
  pipe2(pipe_fr, O_CLOEXEC);

  // this fork call to findrecent() and pipe into write end of pipe_fr
  int pid_fr = fork();
  if (pid_fr == 0) {
    close(pipe_fr[0]);
    dup2(pipe_fr[1], STDOUT_FILENO);
    close(pipe_fr[1]);
    return;
  } // end fork fr

  close(pipe_fr[1]);

  int fd_fzf = fzf_fork(pipe_fr[0], options, argv);

  kill(pid_fr, SIGTERM);
  waitpid(pid_fr, NULL, 0);

  char filebuff[FR_PATH_MAX];
  char *filepath = filebuff;
  ssize_t len_filepath = read(fd_fzf, filebuff, sizeof(filebuff)) - 1;
  close(fd_fzf);

  if (len_filepath < 0) // fzf aborted
    exit(0);

  if (!options->hide_date) {
    filepath = strchr(filebuff, FIELD_SEP[0]);
    if (!filepath)
      exit(1);
    filepath += sizeof(FIELD_SEP) - 1;
    len_filepath -= filepath - filebuff;
  }
  
  int fd_query = query_fork(filepath, len_filepath);

  char query[FR_PATH_MAX] = {0};
  int len_query = read(fd_query, query, sizeof(query));
  close(fd_query);

  if (len_query <= 0) // query aborted
    exit(0);

  exec_query(query, filepath);
}

void fill_preview_cmd(char* preview, struct options *options)
{
  char* cur = preview;

  push_cur(cur, "--preview=");
  if(options->search_type == SEARCH_DIRECTORIES && options->fzf_pane != FZF_PANE_NONE) {
    push_cur(cur, "ls -lth --color -- ");
    push_column_id(cur);
  }
  else {
    switch (options->fzf_pane) {
      case FZF_PANE_CAT:
        push_cur(cur, "cat -- ");
        push_column_id(cur);
        break;
      case FZF_PANE_BAT:
        push_cur(cur, BAT_CMD " --style='changes' --color always -- ");
        push_column_id(cur);
        break;
      case FZF_PANE_NONE: default:
        break;
    }
  }
}

void fill_reload_cmd(char* reload, char** argv)
{
  char* cur = reload;

  push_cur(cur, "--bind=ctrl-r:reload(");
  push_str(cur, *argv); argv++;
  push_cur(cur, " --__force-print0 ");
  while(*argv) {
    push_str(cur, *argv); argv++;
    *cur++ = ' ';
  }
  push_cur(cur, ")");
}

int fzf_fork(int fd_fr, struct options *options, char** argv)
{
  char preview_cmd[512] = "";
  char reload_cmd[512] = "";

  char* fzf_argv[] = {
    FZF_CMD,
    "--read0",
    "--print0",
    "--ansi",                                                 // for color
    "+s",                                                     // do not sort result
    "-d" FIELD_SEP,                                           // delimiter is the 'unit separator' \x1f 
    "--bind=ctrl-p:toggle-preview",                           // bind ctrl+p to toggle the pane visibility
    "--bind=ctrl-l:toggle-preview-wrap",                      // bind ctrl+l to toggle the line wrap in the the pane
    options->hide_date ? "--with-nth=-1" : "--with-nth=1,-1", // last field is the non-shorten path to the file, and should not be displayed
    options->fzf_search_date ? "--nth=.." : "--nth=-1",       // set fields to search in
    options->fzf_wrap_entry ? "--wrap" : "--no-wrap",         // line break if the entry is too long

    preview_cmd, 
    reload_cmd, 
    NULL,
  };

  fill_preview_cmd(preview_cmd, options);
  fill_reload_cmd(reload_cmd, argv);

  int pipe_fzf[2];
  pipe2(pipe_fzf, O_CLOEXEC);

  // this fork read pipe_fr and pipe into fzf
  int pid_fzf = fork();
  if (pid_fzf == 0) {
    dup2(pipe_fzf[1], STDOUT_FILENO);
    dup2(fd_fr, STDIN_FILENO);

    // launch fzf
    execvp(fzf_argv[0], fzf_argv);
    perror("execvp");
    exit(1); // unreachable
  } // end fork fzf

  close(fd_fr);
  close(pipe_fzf[1]);

  // wait for the entry to be selected in fzf
  waitpid(pid_fzf, NULL, 0);

  return pipe_fzf[0];
}

int query_fork(char *filepath, ssize_t len_filepath)
{
  int pipe_query[2];
  int pipe_file[2];
  pipe2(pipe_query, O_CLOEXEC);
  pipe2(pipe_file, O_CLOEXEC);

  // this fork read fzf result and launch fzf command box
  int pid_query = fork();
  if (pid_query == 0) {
    close(pipe_file[1]);
    close(pipe_query[0]);
    dup2(pipe_query[1], STDOUT_FILENO);
    dup2(pipe_file[0], STDIN_FILENO);
    close(pipe_query[1]);
    close(pipe_file[0]);

    char* box_argv[] = {
      FZF_CMD,
      "--read0",
      "--print0",
      "--bind=enter:print-query",
      "--header=Enter a command, `%` is substituted by the filepath.",
      "--header-first",
      "--disabled",
      "--height=5",
      "--info=hidden",
      "--no-separator",
      "--no-scrollbar",
      "--layout=reverse",
      "--border",
      "--margin=1,5%",
      "--padding=1",
      "--pointer=",
      NULL
    };

    execvp(box_argv[0], box_argv);
    perror("execvp");
    exit(1); // unreachable
  } // end fork query

  close(pipe_file[0]);
  close(pipe_query[1]);

  write(pipe_file[1], filepath, len_filepath);
  close(pipe_file[1]);

  waitpid(pid_query, NULL, 0);

  return pipe_query[0];
}

void exec_query(char* query, char* filepath)
{
  while (*query == ' ') query++;
  if (*query == '\0') {
      printf("%s\n", filepath);
      exit(0);
  }

  char cmd_buf[FR_PATH_MAX];
  char* cur = cmd_buf;
  bool replaced = false;

  fputs("$ ", stderr);
  while (*query) {
    if (*query == '%') {
      if (*(query + 1) == '%') {
        *cur++ = '%';
        fputc('%', stderr);
        query++;
      }
      else {
        replaced = true;
        memcpy(cur, "\"$1\"", 4);
        cur += 4;
        fputs(filepath, stderr);
      }
    }
    else {
      *cur++ = *query;
      fputc(*query, stderr);

    }
    query++;
  }

  if (!replaced) {
    memcpy(cur, " \"$1\"", 5);
    fputc(' ', stderr);
    fputs(filepath, stderr);
    cur += 5;
  }
  *cur = '\0';
  fputc('\n', stderr);

  char *sh_argv[] = {
    "sh",
    "-c",
    cmd_buf,
    "sh",
    filepath,
    NULL
  };

  execvp(sh_argv[0], sh_argv);
  perror("execvp");
  exit(1); // unreachable
}
