# findrecent
Search files and sort them. Almost as fast as regular find without sort.

<div align="center">
<img width="719" alt="image" src="https://github.com/user-attachments/assets/466b8e5e-a23f-4f9b-a579-dece133e7661">
</div>
  
## Build
Compile all files in src, or execute `./build.sh`. Binary is named by default `fr`.

Source `fr_completion.bash` to enable bash completion.

To add or change colors you can check `src/gen_colormap.sh`.

## fzf support
fzf can be enable with the option `--fzf`, fzf must be installed.
- preview pane can be enable with `--fzf-pane <str>`, options are `none`, `cat`, `bat`. bat must be installed.
- if enter is pressed, execute the action define by `--fzf-select <str>`, options are `none`, `cat`, `bat`, `git`, `open`, `exec`. 
- press `ctrl+r` to reload.

## Config file
Command placed in the file `$HOME/.config/findrecent/findrecent.conf` are loaded before command line. The default path is defined in `src/parse_options.c`.

Config file can be ignored by passing `--no-config` in command argument. 

Here is an exemple of config file:
```bash 
--color 

--fzf
--fzf-pane bat
# --fzf-select git

# --threads 1

--exclude ".git"
--exclude ".vscode*"
--exclude ".cache"
```

## Options

- `-f`, `--find-files` : Find files (default).
- `-d`, `--find-directories` : Find directories.
- `-t`, `--sort-type <str>` : Change the sorting criterion, can be `creation`, `access`, `modification` or `size` (default: `modification`).
- `-D`, `--depth <int>` : Maximum depth of search.
- `-r`, `--reverse` : Reverse the order.
- `--color` : Colorize output name (toggle on, off).
- `-T`, `--threads <int>` : Set the number of threads during the file search. It does not affect much because printing is often the bottleneck.
- `--inc-max-fd` : Increase the maximum number of file descriptors opened at the same time (may be necessary with a lot of threads).
- `-e`, `--exclude <path>` : Exclude directory. `*` matches multiple characters, and `?` matches one.
- `--no-exclude` : Do not exclude any path.
- `--fzf` : Show in `fzf` (toggle on, off).
- `--fzf-pane <str>` : Activate `fzf` side pane. Options: `none`, `cat`, `bat`. (default: `cat`)
- `--fzf-select <str>` : Action to execute after selection. Options: `none`, `cat`, `bat`, `git`, `open`, `exec` (default: `exec`).
- `--print-config` : Show configuration.
- `--no-config` : Do not use options from the config file (`$HOME/.config/findrecent/findrecent.conf`).
- `-h`, `--help` : Show help.

## Notes
Parallelized with omp task, each file directory is launched in a new task if the number of links inside is less than a threshold (defined in `src/defs.h`). However, printing is often the bottleneck, so it doesn't affect much the perfs.

Colors are defined in `src/colormap.h`, which is generated with the script `src/gen_colormap.sh`. It use gperf and LS_COLORS file to generate an hashmap (credit: <https://github.com/trapd00r/LS_COLORS>).

Directory color is function of the depth of exploration, color is define in `DIR_COLOR_FUNCTION(depth)` in `src/colormap.h` with is a simple function used to fill ansi color code  `\e[38;5;%dm`. 
