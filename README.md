# findrecent
Search files and sort them. Almost as fast as regular find without sort.

![image](https://github.com/user-attachments/assets/18061252-a22b-491c-a464-6316335c4b96)

## Build
Compile all files in src, or execute `./build.sh`. Binary is named by default `fr`.

To add or change colors you can check `src/gen_colormap.sh`.

## fzf support
fzf can be enable with the option `--fzf`, fzf must be installed.
- preview pane can be enable with `--fzf-pane <str>`, options are `none`, `cat`, `bat`. bat must be installed.
- if enter is pressed, the action define by `--fzf-select <str>`, options are `none`, `cat`, `bat`, `git`, `open`.
- press `ctrl+r` to reload.

## Config file
Command placed in the file `$HOME/.config/findrecent/findrecent.conf` are loaded before command line. The default path is defined in `src/parse_options.c`.

Config file can be ignored by passing `--no-config` in command argument. 

Here is an exemple of config file:
```
--color 

--fzf
--fzf-pane bat
# --fzf-select git

# --threads 1

--exclude .git
--exclude .vscode*
```

## Options

- `-f`, `--find-files` : Find files (default).
- `-d`, `--find-directories` : Find directories.
- `-t`, `--date-type <str>` : Change the sorting criterion, can be `creation`, `access`, or `modification` (default: modification).
- `-D`, `--depth <int>` : Maximum depth of search.
- `-r`, `--reverse` : Reverse the order.
- `--color` : Colorize output name (toggle on, off).
- `-T`, `--threads <int>` : Set the number of threads during the file search. It does not affect much because printing is often the bottleneck.
- `-I`, `--inc-max-fd` : Increase the maximum number of file descriptors opened at the same time (may be necessary with a lot of threads).
- `-e`, `--exclude <path>` : Exclude directory. `*` matches multiple characters, and `?` matches one.
- `--no-exclude` : Do not exclude any path.
- `--fzf` : Show in `fzf` (toggle on, off).
- `--fzf-pane <str>` : Activate `fzf` side pane. Options: `none`, `cat`, `bat`.
- `--fzf-select <str>` : Behavior after selection. Options: `none`, `cat`, `bat`, `git`, `open`.
- `--print-config` : Show configuration.
- `--no-config` : Do not use options from the config file (`$HOME/.config/findrecent/findrecent.conf`).
- `-h`, `--help` : Show help.

## Notes
Parallelized with omp task, each file directory is launched in a new task if the number of links inside is less than a threshold (defined in `src/defs.h`). However, printing is often the bottleneck, so it doesn't affect much the perfs.

Colors are defined in `src/colormap.h`, which is generated with the script `src/gen_colormap.sh`. It use gperf and LS_COLORS file to generate an hashmap (credit: <https://raw.githubusercontent.com/trapd00r/LS_COLORS/master/LS_COLORS>).

Directory color is function of the depth of exploration, color is define in `DIR_COLOR_FUNCTION(depth)` in `src/colormap.h` with is a simple function used to fill ansi color code  `\e[38;5;%dm`. 
