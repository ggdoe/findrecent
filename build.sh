#!/bin/sh

# CFLAGS="-flto -Ofast"
CFLAGS="-flto -O3 -march=native"
WFLAGS="-Wall -Wextra -pedantic"
LFLAGS="-fopenmp"
SRC="src/main.c  src/findrecent.c  src/sortmerge.c  src/entry.c  src/buffer.c  src/parse_options.c  src/launch_fzf.c"
# CFLAGS="-g -ggdb $CFLAGS"

output_name=fr
install_cmd="ln -s $PWD/$output_name ~/.local/bin/$output_name"
echo 
set -xe
# ./src/gen_colormap.sh
gcc $WFLAGS $CFLAGS $SRC $LFLAGS -o $output_name

{ set +x; } 2>/dev/null
echo
echo "install command:  " $install_cmd
echo "bash_completion:  " "source '$PWD/fr_completion.bash'"
