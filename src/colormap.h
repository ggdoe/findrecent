/* C code produced by gperf version 3.1 */
/* Command-line: gperf --language C -t -C -Nget_color -m1000 colormap.gperf  */
/* Computed positions: -k'1-4,9,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif

#line 1 "colormap.gperf"

// Generated with: https://raw.githubusercontent.com/trapd00r/LS_COLORS/master/LS_COLORS
#include <string.h>
#include <stdio.h>

#define DIR_COLOR_FUNCTION(n)  (8 + 17 * n)
#define COLOR_EXEC             "38;5;208;1"
#line 9 "colormap.gperf"

#define TOTAL_KEYWORDS 561
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 19
#define MIN_HASH_VALUE 73
#define MAX_HASH_VALUE 1906
/* maximum key range = 1834, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register size_t len;
{
  static const unsigned short asso_values[] =
    {
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907,   37,   36, 1907, 1907, 1907,   46,   54,
        70,  101,   50,   54,   39,   36,   93, 1907,   37, 1907,
      1907, 1907, 1907, 1907, 1907,   37,   36,   43,   36,   36,
        41,   37,   44,   36,   38, 1907,   37,   40, 1907,   43,
        37,   42,   38,   42,   36,   36,   36, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907,   36, 1907,   96,   48,   37,
        43,  127,  134,  140,  478,  375,  372,  460,  214,   57,
       305,  463,   40,  537,  164,   39,   36,  470,   72,  376,
       458,  509,  315,   37, 1907, 1907,   37, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907, 1907,
      1907, 1907, 1907, 1907, 1907, 1907, 1907
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
      case 7:
      case 6:
      case 5:
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]+1];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

const char *
get_color (str, len)
     register const char *str;
     register size_t len;
{
  static const char* wordlist[] =
    {
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1",
#line 154 "colormap.gperf"
      "38;5;114",
      "1",
#line 181 "colormap.gperf"
      "38;5;81",
      "1",
#line 162 "colormap.gperf"
      "38;5;49",
      "1",
#line 214 "colormap.gperf"
      "38;5;110",
      "1",
#line 191 "colormap.gperf"
      "38;5;110",
      "1",
#line 201 "colormap.gperf"
      "38;5;81",
      "1",
#line 215 "colormap.gperf"
      "38;5;110",
      "1",
#line 182 "colormap.gperf"
      "38;5;81",
      "1",
#line 184 "colormap.gperf"
      "38;5;110",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1",
#line 256 "colormap.gperf"
      "38;5;074;1",
#line 194 "colormap.gperf"
      "38;5;81",
#line 192 "colormap.gperf"
      "38;5;110",
#line 152 "colormap.gperf"
      "38;5;160",
#line 310 "colormap.gperf"
      "38;5;99",
      "1",
#line 193 "colormap.gperf"
      "38;5;81",
      "1",
#line 169 "colormap.gperf"
      "38;5;41",
#line 555 "colormap.gperf"
      "38;5;7",
      "1", "1", "1", "1", "1", "1", "1",
#line 56 "colormap.gperf"
      "38;5;60",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1",
#line 232 "colormap.gperf"
      "38;5;81",
      "1",
#line 138 "colormap.gperf"
      "38;5;172",
#line 336 "colormap.gperf"
      "38;5;115;1",
#line 423 "colormap.gperf"
      "38;5;241",
#line 186 "colormap.gperf"
      "38;5;81",
#line 383 "colormap.gperf"
      "38;5;66",
#line 318 "colormap.gperf"
      "38;5;114",
#line 339 "colormap.gperf"
      "38;5;117",
#line 240 "colormap.gperf"
      "38;5;105;1",
#line 532 "colormap.gperf"
      "38;5;7",
#line 185 "colormap.gperf"
      "38;5;110",
#line 296 "colormap.gperf"
      "38;5;97",
#line 73 "colormap.gperf"
      "38;5;141",
#line 267 "colormap.gperf"
      "38;5;81",
#line 77 "colormap.gperf"
      "38;5;111",
      "1",
#line 314 "colormap.gperf"
      "38;5;114",
#line 279 "colormap.gperf"
      "38;5;242",
      "1",
#line 301 "colormap.gperf"
      "38;5;97",
#line 350 "colormap.gperf"
      "38;5;137;1",
#line 398 "colormap.gperf"
      "38;5;215",
#line 440 "colormap.gperf"
      "38;5;29",
#line 24 "colormap.gperf"
      "38;5;184",
      "1",
#line 137 "colormap.gperf"
      "38;5;172",
#line 557 "colormap.gperf"
      "38;5;7",
#line 205 "colormap.gperf"
      "38;5;81",
      "1",
#line 345 "colormap.gperf"
      "38;5;137;1",
#line 486 "colormap.gperf"
      "38;5;213",
      "1", "1", "1", "1", "1",
#line 533 "colormap.gperf"
      "38;5;7",
      "1",
#line 393 "colormap.gperf"
      "38;5;215",
      "1",
#line 354 "colormap.gperf"
      "38;5;137;1",
      "1",
#line 550 "colormap.gperf"
      "38;5;7",
#line 207 "colormap.gperf"
      "38;5;81",
#line 269 "colormap.gperf"
      "38;5;81",
      "1", "1",
#line 282 "colormap.gperf"
      "38;5;244",
#line 342 "colormap.gperf"
      "38;5;117",
      "1", "1", "1",
#line 217 "colormap.gperf"
      "38;5;219",
#line 536 "colormap.gperf"
      "38;5;7",
#line 370 "colormap.gperf"
      "38;5;136;1",
#line 289 "colormap.gperf"
      "38;5;97",
      "1",
#line 243 "colormap.gperf"
      "38;5;105;1",
#line 410 "colormap.gperf"
      "38;5;124",
      "1",
#line 360 "colormap.gperf"
      "38;5;137;1",
#line 419 "colormap.gperf"
      "38;5;244",
#line 242 "colormap.gperf"
      "38;5;105;1",
#line 468 "colormap.gperf"
      "38;5;192;3",
#line 341 "colormap.gperf"
      "38;5;117",
#line 337 "colormap.gperf"
      "38;5;115;1",
      "1",
#line 338 "colormap.gperf"
      "38;5;117",
#line 477 "colormap.gperf"
      "38;5;192;3",
      "1", "1",
#line 163 "colormap.gperf"
      "38;5;81",
#line 512 "colormap.gperf"
      "38;5;136",
#line 92 "colormap.gperf"
      "38;5;78",
#line 91 "colormap.gperf"
      "38;5;78",
#line 346 "colormap.gperf"
      "38;5;137;1",
      "1", "1", "1", "1",
#line 505 "colormap.gperf"
      "38;5;121",
#line 491 "colormap.gperf"
      "38;5;213",
      "1",
#line 18 "colormap.gperf"
      "38;5;184",
      "1", "1", "1", "1",
#line 482 "colormap.gperf"
      "38;5;213",
#line 487 "colormap.gperf"
      "38;5;213",
      "1", "1",
#line 76 "colormap.gperf"
      "38;5;111;4",
      "1", "1",
#line 216 "colormap.gperf"
      "38;5;81",
#line 198 "colormap.gperf"
      "38;5;81",
      "1",
#line 319 "colormap.gperf"
      "38;5;114",
#line 484 "colormap.gperf"
      "38;5;213",
      "1", "1", "1",
#line 171 "colormap.gperf"
      "38;5;81",
      "1",
#line 149 "colormap.gperf"
      "38;5;41",
#line 409 "colormap.gperf"
      "38;5;124",
#line 474 "colormap.gperf"
      "38;5;192;3",
#line 493 "colormap.gperf"
      "38;5;213",
      "1",
#line 429 "colormap.gperf"
      "38;5;241",
      "1",
#line 316 "colormap.gperf"
      "38;5;114",
      "1",
#line 55 "colormap.gperf"
      "38;5;60",
#line 177 "colormap.gperf"
      "38;5;241",
#line 139 "colormap.gperf"
      "38;5;172",
#line 439 "colormap.gperf"
      "38;5;29",
      "1", "1",
#line 204 "colormap.gperf"
      "38;5;81",
      "1", "1",
#line 200 "colormap.gperf"
      "38;5;81",
#line 340 "colormap.gperf"
      "38;5;117",
      "1",
#line 52 "colormap.gperf"
      "38;5;60",
      "1", "1",
#line 25 "colormap.gperf"
      "38;5;184",
#line 387 "colormap.gperf"
      "38;5;215",
#line 504 "colormap.gperf"
      "38;5;121",
#line 485 "colormap.gperf"
      "38;5;213",
#line 377 "colormap.gperf"
      "38;5;66",
      "1",
#line 39 "colormap.gperf"
      "38;5;178",
#line 206 "colormap.gperf"
      "38;5;81",
#line 60 "colormap.gperf"
      "38;5;60",
#line 211 "colormap.gperf"
      "38;5;81",
#line 518 "colormap.gperf"
      "38;5;239",
      "1", "1", "1", "1", "1",
#line 475 "colormap.gperf"
      "38;5;192;3",
      "1",
#line 564 "colormap.gperf"
      "38;5;7",
#line 352 "colormap.gperf"
      "38;5;137;1",
#line 461 "colormap.gperf"
      "38;5;116",
      "1",
#line 378 "colormap.gperf"
      "38;5;66",
      "1", "1",
#line 209 "colormap.gperf"
      "38;5;81",
#line 414 "colormap.gperf"
      "38;5;124",
      "1", "1",
#line 268 "colormap.gperf"
      "38;5;81",
#line 315 "colormap.gperf"
      "38;5;114",
#line 353 "colormap.gperf"
      "38;5;137;1",
#line 45 "colormap.gperf"
      "38;5;178",
      "1", "1",
#line 172 "colormap.gperf"
      "38;5;81",
      "1",
#line 235 "colormap.gperf"
      "38;5;168",
#line 151 "colormap.gperf"
      "38;5;208",
#line 71 "colormap.gperf"
      "38;5;141",
      "1", "1",
#line 325 "colormap.gperf"
      "38;5;114",
      "1", "1", "1",
#line 481 "colormap.gperf"
      "38;5;213",
      "1", "1", "1", "1",
#line 463 "colormap.gperf"
      "38;5;116",
#line 367 "colormap.gperf"
      "38;5;136;1",
#line 433 "colormap.gperf"
      "38;5;239",
#line 161 "colormap.gperf"
      "38;5;49",
#line 173 "colormap.gperf"
      "38;5;81",
#line 170 "colormap.gperf"
      "38;5;51",
      "1",
#line 551 "colormap.gperf"
      "38;5;7",
      "1",
#line 335 "colormap.gperf"
      "38;5;115",
      "1", "1",
#line 333 "colormap.gperf"
      "38;5;115",
#line 248 "colormap.gperf"
      "38;5;135;1",
      "1", "1", "1", "1", "1", "1", "1",
#line 114 "colormap.gperf"
      "1",
      "1", "1", "1",
#line 53 "colormap.gperf"
      "38;5;60",
      "1",
#line 374 "colormap.gperf"
      "38;5;66",
#line 113 "colormap.gperf"
      "1",
      "1",
#line 349 "colormap.gperf"
      "38;5;137;1",
      "1", "1",
#line 365 "colormap.gperf"
      "38;5;136;1",
#line 19 "colormap.gperf"
      "38;5;184",
      "1", "1", "1", "1",
#line 366 "colormap.gperf"
      "38;5;136;1",
#line 456 "colormap.gperf"
      "38;5;116",
      "1", "1", "1", "1", "1",
#line 492 "colormap.gperf"
      "38;5;213",
      "1", "1",
#line 384 "colormap.gperf"
      "38;5;66",
#line 37 "colormap.gperf"
      "38;5;178",
#line 210 "colormap.gperf"
      "38;5;81",
#line 488 "colormap.gperf"
      "38;5;213",
      "1", "1", "1", "1", "1", "1",
#line 236 "colormap.gperf"
      "38;5;168",
#line 568 "colormap.gperf"
      "38;5;7",
#line 64 "colormap.gperf"
      "38;5;60",
#line 54 "colormap.gperf"
      "38;5;60",
#line 237 "colormap.gperf"
      "38;5;168",
      "1", "1", "1",
#line 208 "colormap.gperf"
      "38;5;81",
#line 562 "colormap.gperf"
      "38;5;7",
#line 250 "colormap.gperf"
      "38;5;135;1",
      "1", "1", "1",
#line 82 "colormap.gperf"
      "38;5;111",
#line 176 "colormap.gperf"
      "38;5;81",
#line 252 "colormap.gperf"
      "38;5;135;1",
      "1",
#line 332 "colormap.gperf"
      "38;5;115",
#line 153 "colormap.gperf"
      "38;5;203",
#line 67 "colormap.gperf"
      "38;5;141",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 150 "colormap.gperf"
      "38;5;41",
      "1",
#line 522 "colormap.gperf"
      "38;5;57",
      "1",
#line 317 "colormap.gperf"
      "38;5;114",
      "1", "1",
#line 534 "colormap.gperf"
      "38;5;7",
      "1",
#line 567 "colormap.gperf"
      "38;5;7",
#line 418 "colormap.gperf"
      "38;5;244",
#line 501 "colormap.gperf"
      "38;5;213",
      "1", "1", "1", "1",
#line 450 "colormap.gperf"
      "38;5;45",
#line 441 "colormap.gperf"
      "38;5;29",
#line 234 "colormap.gperf"
      "38;5;240",
      "1", "1", "1",
#line 285 "colormap.gperf"
      "38;5;97",
      "1",
#line 72 "colormap.gperf"
      "38;5;141",
      "1", "1",
#line 61 "colormap.gperf"
      "38;5;60",
      "1", "1", "1",
#line 469 "colormap.gperf"
      "38;5;192;3",
#line 511 "colormap.gperf"
      "38;5;136",
#line 465 "colormap.gperf"
      "38;5;116",
#line 544 "colormap.gperf"
      "38;5;7",
#line 254 "colormap.gperf"
      "38;5;074;1",
      "1", "1", "1",
#line 175 "colormap.gperf"
      "38;5;81",
      "1", "1", "1", "1", "1",
#line 395 "colormap.gperf"
      "38;5;215",
#line 275 "colormap.gperf"
      "38;5;242",
      "1", "1",
#line 123 "colormap.gperf"
      "1",
#line 124 "colormap.gperf"
      "1",
#line 120 "colormap.gperf"
      "1",
      "1",
#line 122 "colormap.gperf"
      "1",
      "1",
#line 241 "colormap.gperf"
      "38;5;105;1",
#line 396 "colormap.gperf"
      "38;5;215",
      "1", "1", "1", "1", "1", "1",
#line 119 "colormap.gperf"
      "1",
#line 260 "colormap.gperf"
      "38;5;079;1",
      "1", "1",
#line 179 "colormap.gperf"
      "38;5;81",
#line 519 "colormap.gperf"
      "38;5;239",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 263 "colormap.gperf"
      "38;5;079;1",
#line 540 "colormap.gperf"
      "38;5;7",
#line 168 "colormap.gperf"
      "38;5;41",
#line 489 "colormap.gperf"
      "38;5;213",
#line 290 "colormap.gperf"
      "38;5;97",
#line 229 "colormap.gperf"
      "38;5;81",
#line 436 "colormap.gperf"
      "38;5;160;1",
#line 264 "colormap.gperf"
      "38;5;81",
#line 549 "colormap.gperf"
      "38;5;7",
#line 361 "colormap.gperf"
      "38;5;137;1",
#line 434 "colormap.gperf"
      "38;5;248",
      "1", "1", "1",
#line 202 "colormap.gperf"
      "38;5;81",
#line 391 "colormap.gperf"
      "38;5;215",
#line 247 "colormap.gperf"
      "38;5;125;1",
#line 535 "colormap.gperf"
      "38;5;7",
#line 389 "colormap.gperf"
      "38;5;215",
#line 160 "colormap.gperf"
      "38;5;64;1",
#line 498 "colormap.gperf"
      "38;5;213",
      "1",
#line 499 "colormap.gperf"
      "38;5;213",
      "1", "1", "1", "1",
#line 368 "colormap.gperf"
      "38;5;136;1",
#line 28 "colormap.gperf"
      "38;5;178",
#line 500 "colormap.gperf"
      "38;5;213",
      "1", "1", "1",
#line 46 "colormap.gperf"
      "38;5;178",
#line 262 "colormap.gperf"
      "38;5;079;1",
#line 228 "colormap.gperf"
      "38;5;81",
      "1",
#line 93 "colormap.gperf"
      "38;5;112",
#line 69 "colormap.gperf"
      "38;5;141",
#line 220 "colormap.gperf"
      "38;5;81",
#line 427 "colormap.gperf"
      "38;5;241",
      "1", "1",
#line 547 "colormap.gperf"
      "38;5;7",
      "1",
#line 412 "colormap.gperf"
      "38;5;124",
#line 12 "colormap.gperf"
      "38;5;190",
      "1", "1", "1", "1", "1",
#line 444 "colormap.gperf"
      "38;5;45",
#line 166 "colormap.gperf"
      "38;5;41",
      "1",
#line 226 "colormap.gperf"
      "38;5;81",
#line 483 "colormap.gperf"
      "38;5;213",
#line 165 "colormap.gperf"
      "38;5;41",
      "1", "1",
#line 552 "colormap.gperf"
      "38;5;7",
#line 103 "colormap.gperf"
      "1",
#line 513 "colormap.gperf"
      "38;5;136",
      "1",
#line 223 "colormap.gperf"
      "38;5;81",
      "1",
#line 565 "colormap.gperf"
      "38;5;7",
      "1", "1", "1",
#line 143 "colormap.gperf"
      "38;5;172",
#line 558 "colormap.gperf"
      "38;5;7",
      "1", "1",
#line 42 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1",
#line 371 "colormap.gperf"
      "38;5;136;1",
      "1",
#line 63 "colormap.gperf"
      "38;5;60",
      "1", "1", "1",
#line 543 "colormap.gperf"
      "38;5;7",
#line 259 "colormap.gperf"
      "38;5;074;1",
      "1",
#line 416 "colormap.gperf"
      "38;5;244",
#line 570 "colormap.gperf"
      "38;5;42",
#line 480 "colormap.gperf"
      "38;5;213",
#line 47 "colormap.gperf"
      "38;5;178",
      "1", "1", "1",
#line 130 "colormap.gperf"
      "38;5;197",
      "1",
#line 14 "colormap.gperf"
      "38;5;184",
#line 265 "colormap.gperf"
      "38;5;81",
#line 187 "colormap.gperf"
      "38;5;110",
      "1", "1",
#line 351 "colormap.gperf"
      "38;5;137;1",
#line 90 "colormap.gperf"
      "38;5;222",
#line 96 "colormap.gperf"
      "38;5;112",
      "1",
#line 258 "colormap.gperf"
      "38;5;074;1",
#line 407 "colormap.gperf"
      "38;5;124",
      "1",
#line 476 "colormap.gperf"
      "38;5;192;3",
#line 48 "colormap.gperf"
      "38;5;178",
      "1", "1",
#line 548 "colormap.gperf"
      "38;5;7",
      "1", "1",
#line 57 "colormap.gperf"
      "38;5;60",
#line 280 "colormap.gperf"
      "38;5;242",
#line 281 "colormap.gperf"
      "38;5;242",
      "1", "1", "1", "1", "1",
#line 195 "colormap.gperf"
      "38;5;81",
#line 343 "colormap.gperf"
      "38;5;117",
#line 445 "colormap.gperf"
      "38;5;45",
      "1",
#line 11 "colormap.gperf"
      "38;5;253",
      "1", "1", "1", "1", "1", "1",
#line 405 "colormap.gperf"
      "38;5;124",
      "1", "1", "1",
#line 399 "colormap.gperf"
      "38;5;215",
      "1",
#line 541 "colormap.gperf"
      "38;5;7",
#line 159 "colormap.gperf"
      "38;5;222",
      "1", "1", "1",
#line 302 "colormap.gperf"
      "38;5;97",
      "1",
#line 348 "colormap.gperf"
      "38;5;137;1",
#line 324 "colormap.gperf"
      "38;5;114",
#line 305 "colormap.gperf"
      "38;5;97",
      "1",
#line 284 "colormap.gperf"
      "48;5;197;38;5;232;1",
#line 199 "colormap.gperf"
      "38;5;81",
      "1", "1", "1", "1",
#line 117 "colormap.gperf"
      "1",
      "1",
#line 85 "colormap.gperf"
      "38;5;166",
      "1",
#line 571 "colormap.gperf"
      "38;5;243",
      "1",
#line 566 "colormap.gperf"
      "38;5;7",
#line 196 "colormap.gperf"
      "38;5;81",
#line 84 "colormap.gperf"
      "38;5;166",
      "1", "1", "1",
#line 328 "colormap.gperf"
      "38;5;115",
      "1", "1",
#line 80 "colormap.gperf"
      "38;5;111",
#line 303 "colormap.gperf"
      "38;5;97",
#line 470 "colormap.gperf"
      "38;5;192;3",
#line 249 "colormap.gperf"
      "38;5;135;1",
#line 99 "colormap.gperf"
      "38;5;73;4",
#line 224 "colormap.gperf"
      "38;5;81",
#line 94 "colormap.gperf"
      "38;5;112",
#line 376 "colormap.gperf"
      "38;5;66",
#line 83 "colormap.gperf"
      "38;5;166",
      "1", "1",
#line 330 "colormap.gperf"
      "38;5;115",
#line 446 "colormap.gperf"
      "38;5;45",
      "1",
#line 288 "colormap.gperf"
      "38;5;97",
#line 542 "colormap.gperf"
      "38;5;7",
#line 428 "colormap.gperf"
      "38;5;241",
#line 453 "colormap.gperf"
      "38;5;45",
      "1", "1",
#line 502 "colormap.gperf"
      "38;5;121",
      "1", "1",
#line 261 "colormap.gperf"
      "38;5;079;1",
#line 79 "colormap.gperf"
      "38;5;111",
#line 59 "colormap.gperf"
      "38;5;60",
      "1", "1", "1",
#line 473 "colormap.gperf"
      "38;5;192;3",
#line 87 "colormap.gperf"
      "38;5;166",
#line 426 "colormap.gperf"
      "38;5;241",
#line 320 "colormap.gperf"
      "38;5;114",
#line 311 "colormap.gperf"
      "38;5;99",
      "1", "1", "1", "1", "1",
#line 51 "colormap.gperf"
      "38;5;178",
#line 494 "colormap.gperf"
      "38;5;213",
      "1",
#line 68 "colormap.gperf"
      "38;5;141",
#line 559 "colormap.gperf"
      "38;5;7",
#line 174 "colormap.gperf"
      "38;5;81",
#line 95 "colormap.gperf"
      "38;5;76",
      "1", "1", "1",
#line 89 "colormap.gperf"
      "38;5;166;4",
#line 66 "colormap.gperf"
      "38;5;141",
      "1", "1", "1", "1", "1", "1",
#line 327 "colormap.gperf"
      "38;5;115",
#line 514 "colormap.gperf"
      "38;5;217",
#line 270 "colormap.gperf"
      "38;5;240",
      "1", "1",
#line 464 "colormap.gperf"
      "38;5;116",
      "1", "1", "1",
#line 430 "colormap.gperf"
      "38;5;241",
#line 347 "colormap.gperf"
      "38;5;137;1",
      "1",
#line 118 "colormap.gperf"
      "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
#line 133 "colormap.gperf"
      "38;5;240",
#line 307 "colormap.gperf"
      "38;5;99",
#line 58 "colormap.gperf"
      "38;5;60",
      "1",
#line 449 "colormap.gperf"
      "38;5;45",
      "1", "1",
#line 390 "colormap.gperf"
      "38;5;215",
      "1", "1",
#line 35 "colormap.gperf"
      "38;5;142",
#line 392 "colormap.gperf"
      "38;5;215",
#line 425 "colormap.gperf"
      "38;5;241",
#line 447 "colormap.gperf"
      "38;5;45",
#line 462 "colormap.gperf"
      "38;5;116",
#line 382 "colormap.gperf"
      "38;5;66",
#line 495 "colormap.gperf"
      "38;5;213",
#line 452 "colormap.gperf"
      "38;5;45",
      "1", "1",
#line 13 "colormap.gperf"
      "38;5;184",
      "1", "1",
#line 460 "colormap.gperf"
      "38;5;116",
      "1", "1", "1",
#line 520 "colormap.gperf"
      "38;5;239",
#line 537 "colormap.gperf"
      "38;5;7",
#line 435 "colormap.gperf"
      "38;5;248",
#line 344 "colormap.gperf"
      "38;5;137;1",
      "1",
#line 521 "colormap.gperf"
      "38;5;57",
#line 379 "colormap.gperf"
      "38;5;66",
      "1", "1",
#line 331 "colormap.gperf"
      "38;5;115",
#line 134 "colormap.gperf"
      "38;5;240",
      "1",
#line 292 "colormap.gperf"
      "38;5;97",
#line 508 "colormap.gperf"
      "38;5;216",
#line 22 "colormap.gperf"
      "38;5;184",
#line 300 "colormap.gperf"
      "38;5;97",
#line 375 "colormap.gperf"
      "38;5;66",
      "1",
#line 556 "colormap.gperf"
      "38;5;7",
      "1", "1",
#line 278 "colormap.gperf"
      "38;5;242",
#line 23 "colormap.gperf"
      "38;5;184",
#line 212 "colormap.gperf"
      "38;5;81",
      "1", "1",
#line 178 "colormap.gperf"
      "38;5;241",
#line 27 "colormap.gperf"
      "38;5;184",
#line 355 "colormap.gperf"
      "38;5;137;1",
#line 253 "colormap.gperf"
      "38;5;135;1",
      "1", "1", "1", "1",
#line 293 "colormap.gperf"
      "38;5;97",
#line 553 "colormap.gperf"
      "38;5;7",
      "1", "1", "1",
#line 104 "colormap.gperf"
      "1",
      "1",
#line 420 "colormap.gperf"
      "38;5;33",
#line 225 "colormap.gperf"
      "38;5;81",
#line 287 "colormap.gperf"
      "38;5;97",
#line 467 "colormap.gperf"
      "38;5;116",
      "1", "1",
#line 388 "colormap.gperf"
      "38;5;215",
      "1", "1",
#line 283 "colormap.gperf"
      "48;5;197;38;5;232",
#line 381 "colormap.gperf"
      "38;5;66",
      "1", "1", "1",
#line 372 "colormap.gperf"
      "38;5;136;1",
      "1",
#line 326 "colormap.gperf"
      "38;5;114",
#line 373 "colormap.gperf"
      "38;5;136;1",
      "1", "1", "1", "1", "1", "1", "1",
#line 309 "colormap.gperf"
      "38;5;99",
#line 291 "colormap.gperf"
      "38;5;97",
      "1",
#line 356 "colormap.gperf"
      "38;5;137;1",
#line 164 "colormap.gperf"
      "38;5;41",
      "1", "1", "1",
#line 306 "colormap.gperf"
      "38;5;99",
#line 510 "colormap.gperf"
      "38;5;216",
      "1",
#line 128 "colormap.gperf"
      "1",
#line 438 "colormap.gperf"
      "38;5;160;1",
#line 432 "colormap.gperf"
      "38;5;241",
      "1", "1", "1", "1", "1",
#line 529 "colormap.gperf"
      "1",
      "1", "1",
#line 506 "colormap.gperf"
      "38;5;121",
      "1", "1", "1",
#line 239 "colormap.gperf"
      "38;5;90;1",
      "1", "1",
#line 146 "colormap.gperf"
      "38;5;41",
      "1", "1", "1", "1", "1", "1", "1",
#line 364 "colormap.gperf"
      "38;5;136;1",
      "1",
#line 362 "colormap.gperf"
      "38;5;137;1",
#line 322 "colormap.gperf"
      "38;5;114",
      "1", "1", "1", "1",
#line 329 "colormap.gperf"
      "38;5;115",
      "1", "1", "1",
#line 105 "colormap.gperf"
      "1",
#line 121 "colormap.gperf"
      "1",
#line 65 "colormap.gperf"
      "38;5;141",
#line 251 "colormap.gperf"
      "38;5;135;1",
#line 363 "colormap.gperf"
      "38;5;136;1",
      "1", "1",
#line 125 "colormap.gperf"
      "1",
#line 140 "colormap.gperf"
      "38;5;172",
      "1", "1",
#line 490 "colormap.gperf"
      "38;5;213",
      "1",
#line 74 "colormap.gperf"
      "38;5;141",
      "1",
#line 246 "colormap.gperf"
      "38;5;125;1",
      "1", "1", "1",
#line 81 "colormap.gperf"
      "38;5;111",
      "1", "1", "1", "1",
#line 50 "colormap.gperf"
      "38;5;178",
      "1", "1",
#line 448 "colormap.gperf"
      "38;5;45",
#line 221 "colormap.gperf"
      "38;5;81",
#line 213 "colormap.gperf"
      "38;5;81",
      "1",
#line 479 "colormap.gperf"
      "38;5;213",
      "1", "1", "1", "1", "1",
#line 546 "colormap.gperf"
      "38;5;7",
      "1",
#line 62 "colormap.gperf"
      "38;5;60",
      "1", "1", "1",
#line 516 "colormap.gperf"
      "38;5;208",
#line 274 "colormap.gperf"
      "38;5;155",
      "1", "1", "1", "1",
#line 129 "colormap.gperf"
      "1",
      "1", "1", "1", "1",
#line 507 "colormap.gperf"
      "38;5;216",
      "1", "1", "1",
#line 457 "colormap.gperf"
      "38;5;116",
      "1", "1",
#line 273 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1",
#line 411 "colormap.gperf"
      "38;5;124",
      "1",
#line 525 "colormap.gperf"
      "1",
      "1", "1",
#line 183 "colormap.gperf"
      "38;5;110",
      "1", "1",
#line 471 "colormap.gperf"
      "38;5;192;3",
      "1",
#line 437 "colormap.gperf"
      "38;5;160;1",
#line 403 "colormap.gperf"
      "38;5;124",
      "1", "1", "1",
#line 431 "colormap.gperf"
      "38;5;241",
      "1", "1",
#line 231 "colormap.gperf"
      "38;5;81",
      "1", "1", "1", "1",
#line 308 "colormap.gperf"
      "38;5;99",
      "1",
#line 286 "colormap.gperf"
      "38;5;97",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 127 "colormap.gperf"
      "1",
      "1", "1",
#line 126 "colormap.gperf"
      "1",
      "1",
#line 257 "colormap.gperf"
      "38;5;074;1",
      "1", "1", "1",
#line 400 "colormap.gperf"
      "38;5;215",
      "1", "1", "1", "1",
#line 523 "colormap.gperf"
      "38;5;241",
      "1", "1", "1", "1",
#line 321 "colormap.gperf"
      "38;5;114",
#line 49 "colormap.gperf"
      "38;5;178",
#line 538 "colormap.gperf"
      "38;5;7",
#line 219 "colormap.gperf"
      "38;5;81",
      "1",
#line 421 "colormap.gperf"
      "38;5;241",
#line 394 "colormap.gperf"
      "38;5;215",
      "1", "1", "1", "1", "1", "1",
#line 111 "colormap.gperf"
      "1",
#line 424 "colormap.gperf"
      "38;5;241",
      "1", "1", "1", "1",
#line 271 "colormap.gperf"
      "38;5;240",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 404 "colormap.gperf"
      "38;5;124",
#line 108 "colormap.gperf"
      "1",
      "1", "1", "1", "1", "1",
#line 78 "colormap.gperf"
      "38;5;111",
#line 560 "colormap.gperf"
      "38;5;7",
#line 17 "colormap.gperf"
      "38;5;184",
      "1", "1", "1",
#line 43 "colormap.gperf"
      "38;5;178",
#line 218 "colormap.gperf"
      "38;5;219",
#line 157 "colormap.gperf"
      "38;5;222",
#line 496 "colormap.gperf"
      "38;5;213",
#line 459 "colormap.gperf"
      "38;5;116",
      "1", "1", "1", "1", "1", "1", "1",
#line 323 "colormap.gperf"
      "38;5;114",
      "1", "1", "1",
#line 155 "colormap.gperf"
      "38;5;222",
      "1", "1",
#line 244 "colormap.gperf"
      "38;5;125;1",
      "1", "1",
#line 238 "colormap.gperf"
      "38;5;90;1",
      "1",
#line 408 "colormap.gperf"
      "38;5;124",
      "1", "1", "1",
#line 98 "colormap.gperf"
      "38;5;112;4",
      "1", "1", "1", "1", "1",
#line 131 "colormap.gperf"
      "38;5;197",
      "1", "1", "1",
#line 451 "colormap.gperf"
      "38;5;45",
      "1", "1", "1",
#line 334 "colormap.gperf"
      "38;5;115",
#line 26 "colormap.gperf"
      "38;5;184",
      "1", "1", "1",
#line 230 "colormap.gperf"
      "38;5;110",
#line 526 "colormap.gperf"
      "1",
#line 136 "colormap.gperf"
      "38;5;172",
#line 545 "colormap.gperf"
      "38;5;7",
      "1",
#line 188 "colormap.gperf"
      "38;5;110",
      "1", "1", "1", "1",
#line 20 "colormap.gperf"
      "38;5;184",
      "1", "1", "1",
#line 386 "colormap.gperf"
      "38;5;215",
      "1", "1", "1",
#line 517 "colormap.gperf"
      "38;5;166",
#line 304 "colormap.gperf"
      "38;5;97",
      "1", "1", "1", "1", "1",
#line 509 "colormap.gperf"
      "38;5;216",
#line 472 "colormap.gperf"
      "38;5;192;3",
      "1",
#line 478 "colormap.gperf"
      "38;5;213",
      "1",
#line 107 "colormap.gperf"
      "1",
#line 190 "colormap.gperf"
      "38;5;110",
      "1", "1", "1",
#line 569 "colormap.gperf"
      "38;5;7",
      "1", "1",
#line 38 "colormap.gperf"
      "38;5;178",
#line 41 "colormap.gperf"
      "38;5;178",
#line 88 "colormap.gperf"
      "38;5;166;4",
#line 116 "colormap.gperf"
      "1",
      "1",
#line 357 "colormap.gperf"
      "38;5;137;1",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 276 "colormap.gperf"
      "38;5;242",
      "1", "1", "1",
#line 528 "colormap.gperf"
      "1",
      "1", "1", "1",
#line 266 "colormap.gperf"
      "38;5;81",
#line 36 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1", "1",
#line 422 "colormap.gperf"
      "38;5;241",
      "1", "1", "1", "1", "1",
#line 156 "colormap.gperf"
      "38;5;222",
      "1", "1",
#line 503 "colormap.gperf"
      "38;5;121",
      "1", "1", "1",
#line 180 "colormap.gperf"
      "38;5;81",
      "1", "1", "1",
#line 466 "colormap.gperf"
      "38;5;116",
#line 524 "colormap.gperf"
      "1",
      "1", "1", "1", "1",
#line 563 "colormap.gperf"
      "38;5;7",
      "1",
#line 132 "colormap.gperf"
      "38;5;240",
      "1", "1", "1", "1", "1",
#line 297 "colormap.gperf"
      "38;5;97",
      "1",
#line 40 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
#line 380 "colormap.gperf"
      "38;5;66",
      "1", "1", "1", "1", "1", "1",
#line 442 "colormap.gperf"
      "38;5;112",
      "1", "1", "1", "1", "1",
#line 203 "colormap.gperf"
      "38;5;81",
#line 30 "colormap.gperf"
      "38;5;178",
#line 34 "colormap.gperf"
      "38;5;178",
      "1", "1",
#line 167 "colormap.gperf"
      "38;5;41",
      "1",
#line 358 "colormap.gperf"
      "38;5;137;1",
#line 312 "colormap.gperf"
      "38;5;114",
#line 369 "colormap.gperf"
      "38;5;136;1",
#line 222 "colormap.gperf"
      "38;5;110",
      "1", "1", "1", "1", "1", "1",
#line 75 "colormap.gperf"
      "38;5;141",
#line 31 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 530 "colormap.gperf"
      "1",
#line 44 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1",
#line 110 "colormap.gperf"
      "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1",
#line 106 "colormap.gperf"
      "1",
      "1", "1", "1", "1", "1", "1",
#line 141 "colormap.gperf"
      "38;5;172",
      "1",
#line 298 "colormap.gperf"
      "38;5;97",
#line 158 "colormap.gperf"
      "38;5;222",
      "1", "1", "1", "1", "1", "1",
#line 295 "colormap.gperf"
      "38;5;97",
      "1", "1", "1", "1",
#line 515 "colormap.gperf"
      "38;5;97",
      "1",
#line 255 "colormap.gperf"
      "38;5;074;1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1",
#line 402 "colormap.gperf"
      "38;5;124",
      "1", "1", "1",
#line 415 "colormap.gperf"
      "38;5;124",
      "1",
#line 112 "colormap.gperf"
      "1",
#line 294 "colormap.gperf"
      "38;5;97",
      "1", "1", "1", "1", "1",
#line 527 "colormap.gperf"
      "38;5;196",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1",
#line 233 "colormap.gperf"
      "38;5;178",
      "1",
#line 227 "colormap.gperf"
      "38;5;81",
      "1", "1", "1",
#line 21 "colormap.gperf"
      "38;5;184",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1",
#line 145 "colormap.gperf"
      "38;5;41",
#line 33 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1",
#line 313 "colormap.gperf"
      "38;5;114",
      "1", "1",
#line 413 "colormap.gperf"
      "38;5;124",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1",
#line 417 "colormap.gperf"
      "38;5;244",
      "1", "1", "1", "1",
#line 144 "colormap.gperf"
      "38;5;172",
      "1", "1", "1", "1", "1",
#line 245 "colormap.gperf"
      "38;5;125;1",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 554 "colormap.gperf"
      "38;5;7",
      "1", "1", "1", "1", "1", "1",
#line 148 "colormap.gperf"
      "38;5;41",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
#line 277 "colormap.gperf"
      "38;5;242",
      "1",
#line 197 "colormap.gperf"
      "38;5;81",
      "1", "1", "1", "1", "1",
#line 100 "colormap.gperf"
      "38;5;73",
      "1", "1",
#line 97 "colormap.gperf"
      "38;5;112",
      "1", "1",
#line 135 "colormap.gperf"
      "38;5;172",
      "1", "1", "1", "1", "1", "1", "1",
#line 29 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
#line 443 "colormap.gperf"
      "38;5;196",
#line 142 "colormap.gperf"
      "38;5;172",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1",
#line 15 "colormap.gperf"
      "38;5;184",
      "1", "1",
#line 70 "colormap.gperf"
      "38;5;141",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1",
#line 561 "colormap.gperf"
      "38;5;7",
      "1",
#line 397 "colormap.gperf"
      "38;5;215",
#line 86 "colormap.gperf"
      "38;5;166",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1",
#line 115 "colormap.gperf"
      "1",
      "1",
#line 531 "colormap.gperf"
      "1",
      "1", "1", "1", "1",
#line 359 "colormap.gperf"
      "38;5;137;1",
      "1", "1", "1",
#line 385 "colormap.gperf"
      "38;5;215",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1",
#line 455 "colormap.gperf"
      "38;5;116",
#line 539 "colormap.gperf"
      "38;5;11",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1",
#line 102 "colormap.gperf"
      "1",
      "1", "1", "1", "1",
#line 272 "colormap.gperf"
      "38;5;155",
      "1", "1", "1",
#line 454 "colormap.gperf"
      "38;5;39",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1",
#line 109 "colormap.gperf"
      "1",
#line 101 "colormap.gperf"
      "38;5;166",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
#line 458 "colormap.gperf"
      "38;5;116",
#line 299 "colormap.gperf"
      "38;5;97",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1",
#line 401 "colormap.gperf"
      "38;5;215",
      "1",
#line 32 "colormap.gperf"
      "38;5;178",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1",
#line 147 "colormap.gperf"
      "38;5;41",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1",
#line 406 "colormap.gperf"
      "38;5;124",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1",
#line 497 "colormap.gperf"
      "38;5;213",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1", "1", "1", "1", "1", "1", "1",
      "1", "1", "1",
#line 16 "colormap.gperf"
      "38;5;184",
      "1", "1", "1",
#line 189 "colormap.gperf"
      "38;5;110"
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = hash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
            return wordlist[key];
        }
    }
  return "1";
}
#line 572 "colormap.gperf"

