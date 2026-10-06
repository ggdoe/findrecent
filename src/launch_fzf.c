#include "defs.h"

static void fill_preview_cmd(char* preview, struct options *options);
static int fzf_fork(int fd_fr, struct options *options);
static int query_fork(char *filepath, ssize_t len_filepath);
static void exec_query(char* query, char* filepath, ssize_t len_filepath);

#define push_column_id(buffer) strcat(buffer, (options->hide_date ? "{1}" : "{2}"))

void launch_in_fzf(struct options *options)
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

  int fd_fzf = fzf_fork(pipe_fr[0], options);

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
    if (!filepath) {
      perror("strchr");
      exit(1);
    }
    filepath += sizeof(FIELD_SEP) - 1;
    len_filepath -= filepath - filebuff;
  }
  
  int fd_query = query_fork(filepath, len_filepath);

  char query[FR_PATH_MAX] = {0};
  int len_query = read(fd_query, query, sizeof(query));
  close(fd_query);

  if (len_query <= 0) // query aborted
    exit(0);

  exec_query(query, filepath, len_filepath);
}

void fill_preview_cmd(char* preview, struct options *options)
{
  strcat(preview, "--preview=");
  if(options->search_type == SEARCH_DIRECTORIES && options->fzf_pane != FZF_PANE_NONE) {
    strcat(preview, "ls -lth --color -- "); 
    push_column_id(preview);
  }
  else {
    switch (options->fzf_pane) {
      case FZF_PANE_CAT:
        strcat(preview, "cat -- ");
        push_column_id(preview);
        break;
      case FZF_PANE_BAT:
        strcat(preview, BAT_CMD " --style='changes' --color always -- ");
        push_column_id(preview);
        break;
      case FZF_PANE_NONE: default:
        break;
    }
  }
}

int fzf_fork(int fd_fr, struct options *options)
{
  char preview_cmd[512] = "";

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
    NULL,
  };

  fill_preview_cmd(preview_cmd, options);

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

void exec_query(char* query, char* filepath, ssize_t len_filepath)
{
  while (*query == ' ') query++;
  if (*query == '\0') {
      printf("%s\n", filepath);
      exit(0);
  }

  char buf[FZF_MAX_QUERY_SIZE];
  char *argv[FZF_MAX_QUERY_ARGS];
  char* arg = buf;
  int argc = 0;
  bool replaced = false;

  while (*query && argc < FZF_MAX_QUERY_ARGS - 2) {
    while (*query == ' ') query++;
    if (*query == '\0') break;

    argv[argc++] = arg;

    char quote = 0;
    while(*query) {
      if (!quote && (*query == '\'' || *query == '"')) {
        quote = *query;
      }
      else if (*query == quote) {
        quote = 0;
      }
      else if (!quote && *query == ' ') {
        break;
      }
      else if (*query == '%') {
        if (*(query + 1) == '%') {
          *arg++ = '%';
          query++;
        }
        else {
          replaced = true;
          memcpy(arg, filepath, len_filepath);
          arg += len_filepath;
        }
      }
      else {
        *arg++ = *query;
      }
      query++;
    }
    *arg++ = '\0';
  }

  if (!replaced) {
    argv[argc++] = memcpy(arg, filepath, len_filepath + 1);
  }
  argv[argc] = NULL;

  execvp(argv[0], argv);
  perror("execvp");
  exit(1); // unreachable
}
