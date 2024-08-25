#!/bin/sh

# CFLAGS="-g -ggdb -flto -O3"
# CFLAGS="-flto -Ofast"
CFLAGS="-flto -O3"
WFLAGS="-Wall -Wextra -pedantic"
LFLAGS="-fopenmp"

SRC="main.c findrecent.c sortmerge.c entry.c buffer.c parse_options.c launch_fzf.c"

set -xe
gcc $WFLAGS $CFLAGS $SRC $LFLAGS
