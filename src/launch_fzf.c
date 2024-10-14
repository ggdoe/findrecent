#include "defs.h"

static char* stringize_argv(char** argv);
static void fill_preview_cmd(char* preview, struct parsed_options *options);
static void fill_reload_cmd(char* reload, char* cmd_argv);
static void fill_select_cmd(char* select, struct parsed_options *options);

void launch_in_fzf(char** argv, struct parsed_options *options)
{
  char preview_cmd[512] = "";
  char reload_cmd[512] = "";
  char select_cmd[512] = "";

  char* fzf_argv[] = {
    "fzf", 
    "--ansi", 
    "--tac", 
    "+s",
    "-d: ",                                              // delimiter is ': '
    options->fzf_search_date ? "--nth=1.." : "--nth=-1", // so that it dont search in the date 

    preview_cmd, 
    reload_cmd, 
    select_cmd,
    NULL,
  };
  
  // construct cmd_argv
  char* cmd_argv = stringize_argv(argv);

  // fill fzf arguments
  fill_preview_cmd(preview_cmd, options);
  fill_reload_cmd(reload_cmd, cmd_argv);
  fill_select_cmd(select_cmd, options);
  setenv("FZF_DEFAULT_COMMAND", cmd_argv, 1);

  // launch fzf
  if(execvp(fzf_argv[0], fzf_argv) < 0)
    perror("error durring fzf launch.");
  exit(1); // unreachable
}

char* stringize_argv(char** argv)
{
  int cmd_argc = 0;
  for(char** cur=argv; *cur != NULL; cur++)
    cmd_argc += strlen(*cur) + 3; // 2 quotes, 1 space

  char* cmd_argv = (char*)calloc(cmd_argc+1, sizeof(char));
  for(char** cur=argv; *cur != NULL; cur++){
    strcat(cmd_argv, "'");
    strcat(cmd_argv, *cur);
    strcat(cmd_argv, "' ");
  }
  return cmd_argv;
}

void fill_preview_cmd(char* preview, struct parsed_options *options)
{
  strcat(preview, "--preview=");
  if(options->options.search_type == SEARCH_DIRECTORIES && options->fzf_pane != FZF_PANE_NONE)
    strcat(preview, "ls -lth --color {-1}");
  else {
    switch (options->fzf_pane) {
      case FZF_PANE_CAT:
        strcat(preview, "cat {-1}");
        break;
      case FZF_PANE_BAT:
        strcat(preview, "bat --style='changes' --color always {-1}");
        break;
      case FZF_PANE_NONE: default:
        break;
    }
  }
}

void fill_reload_cmd(char* reload, char* cmd_argv)
{
  strcat(reload, "--bind=ctrl-r:reload(");
  strcat(reload, cmd_argv);
  strcat(reload, ")");
}

void fill_select_cmd(char* select, struct parsed_options *options)
{
  strcat(select, "--bind=enter:become(");

  if(options->options.search_type == SEARCH_DIRECTORIES && options->fzf_select != FZF_SELECT_OPEN && options->fzf_select != FZF_SELECT_NONE)
    strcat(select, "ls -lth --color {-1}");
  else {
    switch (options->fzf_select) {
      case FZF_SELECT_CAT:
        strcat(select, "cat {-1})");
        break;
      case FZF_SELECT_BAT:
        strcat(select, "bat --style=changes,numbers --color always {-1}");
        break;
      case FZF_SELECT_GIT:
        strcat(select, 
        "if ( git -C $(dirname {-1}) rev-parse 2>/dev/null );"
        "then "
        "git -C $(dirname {-1}) diff $(basename {-1});"
        "else echo cannot show git changes, \\`{-1}\\` is not in a git directory. ; fi;"
        );
        break;
      case FZF_SELECT_EXEC:
        strcat(select, 
        "echo {-1} | fzf "
        // "--header \"Enter a command: \" --header-first "
        // "--bind=enter:become:\"\\$FZF_QUERY {-1}\" "
        "--header \"Enter a command, \\`%\\` is substituted by the filepath. \" --header-first "
        "--bind=enter:become:'eval $(echo $FZF_QUERY | sed \"s#%#\\{}#g;t;s#\\$# \\{}#\" )' "
        "--disabled --height 5 --info hidden --no-separator --no-scrollbar "
        "--layout reverse --border --margin 1,5% --padding=1 --pointer \"\" "
        );
        break;
      case FZF_SELECT_OPEN:
        strcat(select, "open {-1}");
        break;
      case FZF_SELECT_NONE: default:
        strcat(select, "echo {-1}");
        break;
    }
  }
  strcat(select, ")");
}
