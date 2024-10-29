#/usr/bin/env bash

_fr_completions()
{
  local cur prev opts
  COMPREPLY=()
  cur="${COMP_WORDS[COMP_CWORD]}"
  prev="${COMP_WORDS[COMP_CWORD-1]}"
  opts=(
    -find-files
    -find-directories
    -sort-type
    -depth
    -reverse
    -color
    -threads
    -inc-max-fd
    -task-threshold
    -exclude
    -no-exclude
    -fzf
    -fzf-pane
    -fzf-select
    -fzf-search-date
    -print-config
    -no-config
    -help
  )

  case "${prev}" in
  -t | -?(-)sort-type)
    COMPREPLY=( $(compgen -W "creation access modification size" -- "$cur") )
    return 0
    ;;
  -D | -?(-)depth | \
  -T | -?(-)threads | \
       -?(-)task-threshold)
    return 0
    ;;
  -e | -?(-)exclude)
    _filedir
    return 0
    ;;
       -?(-)fzf-pane)
    COMPREPLY=( $(compgen -W "none cat bat" -- "$cur") )
    return 0
    ;;
       -?(-)fzf-select)
    COMPREPLY=( $(compgen -W "none cat bat git open" -- "$cur") )
    return 0
    ;;
  esac
  
  if [[ "$cur" =~ ^-- ]]; then
    COMPREPLY=( $(compgen -W "${opts[*]/#/-}" -- "$cur") )
    return 0
  elif [[ "$cur" =~ ^- ]]; then
    COMPREPLY=( $(compgen -W "${opts[*]}" -- "$cur") )
    return 0
  fi 

    _filedir -d
  return 0
}

complete -F _fr_completions fr
