#!/bin/sh

# CFLAGS="-flto -Ofast"
CFLAGS="-flto -O3"
WFLAGS="-Wall -Wextra -pedantic"
LFLAGS="-fopenmp"

output_name=fr
install_cmd="ln -s $PWD/$output_name ~/.local/bin/$output_name"
# echo install command: $install_cmd

SRC="main.c findrecent.c sortmerge.c entry.c buffer.c parse_options.c launch_fzf.c"

set -xe
gcc $WFLAGS $CFLAGS $SRC $LFLAGS -o $output_name
