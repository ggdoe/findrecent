#!/bin/bash

set -e

filename_gperf="colormap.gperf"
filename_out="$(dirname "$0")/colormap.h"
remote_ls_colors="https://raw.githubusercontent.com/trapd00r/LS_COLORS/master/LS_COLORS" # nice
curl -s $remote_ls_colors > LS_COLORS_tmp

default_color="\"1\""
exec_color="$(cat LS_COLORS_tmp | awk '/^EXEC/{print $2}')"

# manual color entries (must start with dot .)
echo """
.cu   38;5;42
.conf 38;5;243
""" >> LS_COLORS_tmp 


# creating gperf file
echo "%{
// Generated with: "$remote_ls_colors"
#include <string.h>
#include <stdio.h>

#define DIR_COLOR_FUNCTION(n)  (((3 + 19 * n) % 214) + 17) // valid color range: 17-230
#define COLOR_EXEC             \"$exec_color\"
%}
struct colormap {const char* ext; const char* color;};
%%" > $filename_gperf
cat LS_COLORS_tmp | 
sed -n "/^\./s/^\.//p" | 
sed -r "/\{|\}|\[|\]|\*/d" | 
awk '{printf "%s, \"%s\"\n", $1, $2}' >> $filename_gperf
echo %% >> $filename_gperf


# remove keys from gperf, only keeping values (color), 
# because we dont care if we use the wrong color for unknown files (that may be a bad idea)
# you may want increase -m option to improve quality of hashmap (exemple -m1000 if you have some time to spend)
gperf --language C -t -C -N"get_color" -m20 $filename_gperf | 
sed -e 's/{".\+", \(".\+"\)}/\1/'                                                    `# remove keys from wordlist`                \
    -e 's/{""}/'$default_color'/g'                                                   `# replace empty values with $default_color` \
    -e '/struct colormap.*;$/d'                                                      `# remove struct def`                        \
    -e 's/struct colormap wordlist/char* wordlist/'                                  `# change type of wordlist`                  \
    -e 's/struct colormap/char/'                                                     `# change type of the function`              \
    -e '/wordlist\[key\]\.name/,+2d'                                                 `# do not check the key`                     \
    -e 's/return &wordlist/return wordlist/;s/return 0/return '$default_color'/ '   `# change return type of wordlist`            \
    -e '/(str, len)$/{s/str, len)//;n;s/register //;s/;/,/;n;s/register //;s/;/ )/}' `# remove old function style definition`     \
> $filename_out 

rm $filename_gperf LS_COLORS_tmp
