#!/bin/python3

import os
import numpy as np
import requests
output_file="./color_list.h"

color = lambda c: f"\033[38;5;{c}m"
color_end = "\033[0m"
dir_color_function = "8 + 17 * n"

# use local $LS_COLOR or wget it from the web (https://github.com/trapd00r/LS_COLORS)
USE_REMOTE_LS_COLORS = True
remote_ls_colors="https://raw.githubusercontent.com/trapd00r/LS_COLORS/master/LS_COLORS" # nice

list_color=[]
len_max=[0,0]
forgiven_character="{}[]*,"
manual_entries=[
  ("cu",   "38;5;42",  "// CUDA"),
  ("conf", "38;5;243", "// config files"),
]
entry_exec=["", "1;91"]; exec_str=("EXEC", "ex")
entry_default=["", "0"]

def firstchar(s):
  for c in s:
    if c != ' ' and c != '\t':
      return c
  return ''

## setup list_color
if not USE_REMOTE_LS_COLORS:
  for line in os.getenv("LS_COLORS").split(':'):
    fc = firstchar(line)
    if fc == '' or fc == '#': continue
    splitted = line.split("=", maxsplit=2)
    if line[1] == '.':
      splitted[0] = splitted[0][2:]
      if any(c in splitted[0] for c in forgiven_character):
        continue
      list_color.append(splitted)
      len_max = list(map(max, map(len, splitted), len_max))
    elif any(e in line for e in exec_str):
      entry_exec[1] = splitted[1]
else:
  for line in requests.get(remote_ls_colors).iter_lines(decode_unicode=True):
    fc = firstchar(line)
    if fc == '' or fc == '#': continue
    splitted = line.split(maxsplit=2)
    if line[0] == '.':
      if any(c in splitted[0] for c in forgiven_character):
        continue
      splitted[0] = splitted[0][1:]
      list_color.append(splitted)
      len_max = list(map(max, map(len, splitted), len_max))
    elif any(e in line for e in exec_str):
      entry_exec = line.split(maxsplit=2)

## gen from file "LS_COLORS"
# file = open("LS_COLORS", "r")
# for line in file:
#   fc = firstchar(line)
#   if fc == '' or fc == '#': continue
#   splitted = line.split(maxsplit=2)
#   if line[0] == '.':
#     if any(c in splitted[0] for c in forgiven_character):
#       continue
#     splitted[0] = splitted[0][1:]
#     list_color.append(splitted)
#     len_max = list(map(max, map(len, splitted), len_max))
#   elif any(e in line for e in exec_str):
#     entry_exec = line.split(maxsplit=2)
# file.close()

for e in manual_entries:
  if any([e[0] == l[0] for l in list_color]):
      manual_entries.remove(e)

entry_exec[0] = ""
entry_exec[2] = "// executable"

## setup strings
header = """// Generated""" + ( f" from: {remote_ls_colors}" if USE_REMOTE_LS_COLORS else "") + """
#ifndef _COLOR_LIST_H_
#define _COLOR_LIST_H_

#define DIR_COLOR_FUNCTION(n)  (""" + dir_color_function + """)

struct color_map {
  const char* ext; 
  const char* color;
};

static const 
struct color_map color_list[] = 
{
"""

newline='\n' # cannot put backslash in f-string in python<3.12
pusher = lambda ext, color, comments="": f'  {{"{ext}",{" "*(len_max[0] - len(ext))} "{color}"{" "*(len_max[1] - len(color))}}},  {comments.replace("#", "//").replace(newline, "")}\n'

footer = ""
if(len(manual_entries) > 0):
  footer+= "\n// manual entries\n"
  for e in manual_entries:
    footer+=pusher(*e)
footer+= """
// default\n"""        + \
pusher(*entry_exec)    + \
pusher(*entry_default) + \
"""};
#define sizeof_color_list  (sizeof(color_list)/sizeof(*color_list) - 2ULL)
#define COLOR_EXEC         (sizeof(color_list)/sizeof(*color_list) - 2ULL)
#define COLOR_DEFAULT      (sizeof(color_list)/sizeof(*color_list) - 1ULL)

#endif //_COLOR_LIST_H_
"""


# work
with open(output_file, "w") as f:
  f.write(header)
  for entry in list_color:
    f.write(pusher(*entry))
  f.write(footer)
print("done: ", output_file)

# print(header, end='')
# for entry in list_color:
#   print(pusher(*entry), end='')
# print(footer, end='')

