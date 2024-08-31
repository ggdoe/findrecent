#!/bin/bash

set -e

filename_gperf="colormap.gperf"
filename_out="src/colormap.h"
remote_ls_colors="https://raw.githubusercontent.com/trapd00r/LS_COLORS/master/LS_COLORS" # nice
curl -s $remote_ls_colors > LS_COLORS

default_color="\"1\""
exec_color="$(cat LS_COLORS | awk '/^EXEC/{print $2}')"
echo """
.cu   38;5;42
.conf 38;5;243
""" >> LS_COLORS # manual color entries (must start with dot .)


# creating gperf file
echo "%{
// Generated with: "$remote_ls_colors"
#include <string.h>
#include <stdio.h>

#define DIR_COLOR_FUNCTION(n)  (8 + 17 * n)
#define COLOR_EXEC             \"$exec_color\"
%}
struct colormap {const char* ext; const char* color;};
%%" > $filename_gperf
cat LS_COLORS | 
sed -n "/^\./s/^\.//p" | 
sed -r "/ 1 |\{|\}|\[|\]|\*/d" | 
awk '{printf "%s, \"%s\"\n", $1, $2}' >> $filename_gperf
echo %% >> $filename_gperf


# remove key for gperf, only keeping values (color), 
# because we dont care if we use the wrong color for unknown files (maybe that's a bad idea)
gperf --language C -t -C -N"get_color" -m20 $filename_gperf | 
sed 's/{".\+", \(".\+"\)}/\1/;s/{""}/'$default_color'/g' | # remove keys from wordlist
sed '/struct colormap.*;$/d' | # remove struct def
sed 's/struct colormap wordlist/char* wordlist/' | # change type of wordlist
sed 's/struct colormap/char/' | # change type of the function
sed '/wordlist\[key\]\.name/,+2d' | # do not check the key
sed 's/return &wordlist/return wordlist/;s/return 0/return '$default_color'/ ' > $filename_out


rm $filename_gperf LS_COLORS
