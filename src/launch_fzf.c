#include "defs.h"

static char* stringize_argv(char** argv);
static void fill_preview_cmd(char* preview, struct options *options);
static void fill_reload_cmd(char* reload, char* cmd_argv);
static void fill_select_cmd(char* select, struct options *options);

#define push_column_id(buffer) strcat(buffer, (options->hide_date ? "{1}" : "{2}"))


void launch_in_fzf(char** argv, struct options *options)
{
  char preview_cmd[512] = "";
  char reload_cmd[512] = "";
  char select_cmd[1024] = "";

  char* fzf_argv[] = {
    "fzf",
    "--ansi",                                                 // for color
    "--tac",                                                  // revert order
    "+s",                                                     // do not sort result
    "-d\x1f ",                                                // delimiter is the 'unit separator' \x1f 
    "--bind=ctrl-p:toggle-preview",                           // bind ctrl+p to toggle the pane visibility
    "--bind=ctrl-l:toggle-preview-wrap",                      // bind ctrl+l to toggle the line wrap in the the pane
    options->hide_date ? "--with-nth=-1" : "--with-nth=1,-1", // last field is the non-shorten path to the file, and should not be displayed
    options->fzf_search_date ? "--nth=.." : "--nth=-1",       // set fields to search in
    options->fzf_wrap_entry ? "--wrap" : "--no-wrap",         // line break if the entry is too long

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

void fill_preview_cmd(char* preview, struct options *options)
{
  strcat(preview, "--preview=");
  if(options->search_type == SEARCH_DIRECTORIES && options->fzf_pane != FZF_PANE_NONE) {
    strcat(preview, "ls -lth --color "); 
    push_column_id(preview);
  }
  else {
    switch (options->fzf_pane) {
      case FZF_PANE_CAT:
        strcat(preview, "cat ");
        push_column_id(preview);
        break;
      case FZF_PANE_BAT:
        strcat(preview, "bat --style='changes' --color always ");
        push_column_id(preview);
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

void fill_select_cmd(char* select, struct options *options)
{
  strcat(select, "--bind=enter:become(");

  if(options->search_type == SEARCH_DIRECTORIES && options->fzf_select != FZF_SELECT_OPEN && options->fzf_select != FZF_SELECT_EXEC && options->fzf_select != FZF_SELECT_NONE) {
    strcat(select, "ls -lth --color ");
    push_column_id(select);
  }
  else {
    switch (options->fzf_select) {
      case FZF_SELECT_CAT:
        strcat(select, "cat )");
        push_column_id(select);
        break;
      case FZF_SELECT_BAT:
        strcat(select, "bat --style=changes,numbers --color always ");
        push_column_id(select);
        break;
      case FZF_SELECT_GIT:
        strcat(select, 
        "filename='");
        push_column_id(select);
        strcat(select, "'; "
        "if ( git -C $(dirname $filename) rev-parse 2>/dev/null );"
        "then "
        "git -C $(dirname $filename) diff $(basename $filename);"
        "else echo cannot show git changes, \\`$filename\\` is not in a git directory. ; fi;"
        );
        break;
      case FZF_SELECT_EXEC:
        strcat(select, "printf -- \"%s\n\" ");
        push_column_id(select);
        strcat(select, 
        "| fzf "
        "--header \"Enter a command, \\`%\\` is substituted by the filepath. \" --header-first "
        "--bind=enter:become:'"
        "printf -v file \"%q\" \\{}; "             // espace the filename
        "printf -v cmd \"%q\" \"$FZF_QUERY\"; "    // get the command and escape it
        "cmd=${cmd//\\\\ / }; "                    // unescape spaces
        "cmd=${cmd//#/\\\\#}; "                    // escape # (printf does not do it)
        "[ -z \"${FZF_QUERY// }\" ] && cmd=echo; " // if empty command, use echo
        "cmd=${cmd//%%/\x1f}; "                    // escape %%
        "if [ -z \"${cmd//[^%]}\" ]; then "        // if no % in command
          "cmd=\"$cmd $file\"; "                   // append the filename
        "else "
          "cmd=\"${cmd//%/$file}\"; "              // substitute % by filename
        "fi; "
        "cmd=\"${cmd//\x1f/%}\"; "                 // restore escaped %%
        "eval \"$cmd\"; "                          // execute command
        "' "
        "--disabled --height 5 --info hidden --no-separator --no-scrollbar "
        "--layout reverse --border --margin 1,5% --padding=1 --pointer \"\" "
        );
        break;
      case FZF_SELECT_OPEN:
        strcat(select, "open ");
        push_column_id(select);
        break;
      case FZF_SELECT_NONE: default:
        strcat(select, "echo ");
        push_column_id(select);
        break;
    }
  }
  strcat(select, ")");
}
