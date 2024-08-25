// Generated from: https://raw.githubusercontent.com/trapd00r/LS_COLORS/master/LS_COLORS
#ifndef _COLOR_LIST_H_
#define _COLOR_LIST_H_

#define DIR_COLOR_FUNCTION(n)  (8 + 17 * n)

struct color_map {
  const char* ext; 
  const char* color;
};

static const 
struct color_map color_list[] = 
{
  {"txt",                 "38;5;253"           },  // Plain-text
  {"log",                 "38;5;190"           },  // Logs
  {"adoc",                "38;5;184"           },  // Markup
  {"asciidoc",            "38;5;184"           },  // Markup
  {"etx",                 "38;5;184"           },  // Markup
  {"info",                "38;5;184"           },  // Markup
  {"markdown",            "38;5;184"           },  // Markup
  {"md",                  "38;5;184"           },  // Markup
  {"mkd",                 "38;5;184"           },  // Markup
  {"mdx",                 "38;5;184"           },  // Markup
  {"nfo",                 "38;5;184"           },  // Markup
  {"org",                 "38;5;184"           },  // Markup
  {"norg",                "38;5;184"           },  // Markup
  {"pod",                 "38;5;184"           },  // Markup
  {"rst",                 "38;5;184"           },  // Markup
  {"tex",                 "38;5;184"           },  // Markup
  {"textile",             "38;5;184"           },  // Markup
  {"bib",                 "38;5;178"           },  // Data store // non-relational
  {"json",                "38;5;178"           },  // Data store // non-relational
  {"jsonc",               "38;5;178"           },  // Data store // non-relational
  {"json5",               "38;5;178"           },  // Data store // non-relational
  {"hjson",               "38;5;178"           },  // Data store // non-relational
  {"jsonl",               "38;5;178"           },  // Data store // non-relational
  {"jsonnet",             "38;5;178"           },  // Data store // non-relational
  {"libsonnet",           "38;5;142"           },  // Data store // non-relational
  {"ndjson",              "38;5;178"           },  // Data store // non-relational
  {"msg",                 "38;5;178"           },  // Data store // non-relational
  {"pgn",                 "38;5;178"           },  // Data store // non-relational
  {"rss",                 "38;5;178"           },  // Data store // non-relational
  {"xml",                 "38;5;178"           },  // Data store // non-relational
  {"fxml",                "38;5;178"           },  // Data store // non-relational
  {"toml",                "38;5;178"           },  // Data store // non-relational
  {"yaml",                "38;5;178"           },  // Data store // non-relational
  {"yml",                 "38;5;178"           },  // Data store // non-relational
  {"RData",               "38;5;178"           },  // Data store // non-relational
  {"rdata",               "38;5;178"           },  // Data store // non-relational
  {"xsd",                 "38;5;178"           },  // Data store // non-relational
  {"dtd",                 "38;5;178"           },  // Data store // non-relational
  {"sgml",                "38;5;178"           },  // Data store // non-relational
  {"rng",                 "38;5;178"           },  // Data store // non-relational
  {"rnc",                 "38;5;178"           },  // Data store // non-relational
  {"accdb",               "38;5;60"            },  // Data store // MS Access
  {"accde",               "38;5;60"            },  // Data store // MS Access
  {"accdr",               "38;5;60"            },  // Data store // MS Access
  {"accdt",               "38;5;60"            },  // Data store // MS Access
  {"db",                  "38;5;60"            },  // Data store
  {"fmp12",               "38;5;60"            },  // Data store
  {"fp7",                 "38;5;60"            },  // Data store
  {"localstorage",        "38;5;60"            },  // Data store
  {"mdb",                 "38;5;60"            },  // Data store
  {"mde",                 "38;5;60"            },  // Data store
  {"sqlite",              "38;5;60"            },  // Data store // SQLite
  {"typelib",             "38;5;60"            },  // Data store
  {"nc",                  "38;5;60"            },  // Data store // NetCDF
  {"azw",                 "38;5;141"           },  // Documents // binary
  {"azw3",                "38;5;141"           },  // Documents // binary
  {"cbr",                 "38;5;141"           },  // Documents // binary
  {"cbz",                 "38;5;141"           },  // Documents // binary
  {"chm",                 "38;5;141"           },  // Documents // binary
  {"djvu",                "38;5;141"           },  // Documents // binary
  {"fb2",                 "38;5;141"           },  // Documents // binary
  {"pdf",                 "38;5;141"           },  // Documents // binary
  {"PDF",                 "38;5;141"           },  // Documents // binary
  {"mobi",                "38;5;141"           },  // Documents // binary
  {"epub",                "38;5;141"           },  // Documents // binary
  {"docm",                "38;5;111;4"         },  // Documents // with macros
  {"doc",                 "38;5;111"           },  // Documents
  {"docx",                "38;5;111"           },  // Documents
  {"odb",                 "38;5;111"           },  // Documents
  {"odt",                 "38;5;111"           },  // Documents
  {"rtf",                 "38;5;111"           },  // Documents
  {"pages",               "38;5;111"           },  // Documents
  {"odp",                 "38;5;166"           },  // Presentation
  {"pps",                 "38;5;166"           },  // Presentation
  {"ppt",                 "38;5;166"           },  // Presentation
  {"pptx",                "38;5;166"           },  // Presentation
  {"ppts",                "38;5;166"           },  // Presentation
  {"pptxm",               "38;5;166;4"         },  // Presentation (with macros)
  {"pptsm",               "38;5;166;4"         },  // Presentation (with macros)
  {"prisma",              "38;5;222"           },  // Prisma Schema/Config
  {"csv",                 "38;5;78"            },  // Spreadsheet (plain text)
  {"tsv",                 "38;5;78"            },  // Spreadsheet (plain text)
  {"numbers",             "38;5;112"           },  // Spreadsheet
  {"ods",                 "38;5;112"           },  // Spreadsheet
  {"xla",                 "38;5;76"            },  // Spreadsheet
  {"xls",                 "38;5;112"           },  // Spreadsheet
  {"xlsx",                "38;5;112"           },  // Spreadsheet
  {"xlsxm",               "38;5;112;4"         },  // Spreadsheet (with macros)
  {"xltm",                "38;5;73;4"          },  // Spreadsheet (with macros)
  {"xltx",                "38;5;73"            },  // Spreadsheet (with macros)
  {"key",                 "38;5;166"           },  // License keys
  {"ini",                 "1"                  },  // Configs
  {"plist",               "1"                  },  // Configs
  {"profile",             "1"                  },  // Configs
  {"bash_profile",        "1"                  },  // Configs
  {"bash_login",          "1"                  },  // Configs
  {"bash_logout",         "1"                  },  // Configs
  {"zshenv",              "1"                  },  // Configs
  {"zprofile",            "1"                  },  // Configs
  {"zlogin",              "1"                  },  // Configs
  {"zlogout",             "1"                  },  // Configs
  {"viminfo",             "1"                  },  // Configs
  {"pcf",                 "1"                  },  // Configs
  {"psf",                 "1"                  },  // Configs
  {"hidden-color-scheme", "1"                  },  // Configs
  {"hidden-tmTheme",      "1"                  },  // Configs
  {"last-run",            "1"                  },  // Configs
  {"merged-ca-bundle",    "1"                  },  // Configs
  {"sublime-build",       "1"                  },  // Configs
  {"sublime-commands",    "1"                  },  // Configs
  {"sublime-keymap",      "1"                  },  // Configs
  {"sublime-settings",    "1"                  },  // Configs
  {"sublime-snippet",     "1"                  },  // Configs
  {"sublime-project",     "1"                  },  // Configs
  {"sublime-workspace",   "1"                  },  // Configs
  {"tmTheme",             "1"                  },  // Configs
  {"user-ca-bundle",      "1"                  },  // Configs
  {"rstheme",             "1"                  },  // Configs
  {"epf",                 "1"                  },  // Configs
  {"git",                 "38;5;197"           },  // Version control
  {"github",              "38;5;197"           },  // Version control
  {"gitignore",           "38;5;240"           },  // Version control
  {"gitattributes",       "38;5;240"           },  // Version control
  {"gitmodules",          "38;5;240"           },  // Version control
  {"awk",                 "38;5;172"           },  // Code (shell)
  {"bash",                "38;5;172"           },  // Code (shell)
  {"bat",                 "38;5;172"           },  // Code (shell)
  {"BAT",                 "38;5;172"           },  // Code (shell)
  {"sed",                 "38;5;172"           },  // Code (shell)
  {"sh",                  "38;5;172"           },  // Code (shell)
  {"zsh",                 "38;5;172"           },  // Code (shell)
  {"fish",                "38;5;172"           },  // Code (shell)
  {"vim",                 "38;5;172"           },  // Code (shell)
  {"kak",                 "38;5;172"           },  // Code (shell)
  {"ahk",                 "38;5;41"            },  // Code (interpreted) (AutoHotKey)
  {"py",                  "38;5;41"            },  // Code (interpreted) (Python)
  {"ipynb",               "38;5;41"            },  // Code (interpreted) (Python)
  {"xsh",                 "38;5;41"            },  // Code (interpreted) (xonsh)
  {"rb",                  "38;5;41"            },  // Code (interpreted) (ruby)
  {"gemspec",             "38;5;41"            },  // Code (interpreted) (ruby)
  {"pl",                  "38;5;208"           },  // Code (interpreted) (Perl)
  {"PL",                  "38;5;160"           },  // Code (interpreted) (Perl)
  {"pm",                  "38;5;203"           },  // Code (interpreted) (Perl)
  {"t",                   "38;5;114"           },  // Code (interpreted) (Perl)
  {"msql",                "38;5;222"           },  // Code (SQL)
  {"mysql",               "38;5;222"           },  // Code (SQL)
  {"prql",                "38;5;222"           },  // Code (SQL)
  {"pgsql",               "38;5;222"           },  // Code (SQL)
  {"sql",                 "38;5;222"           },  // Code (SQL)
  {"tcl",                 "38;5;64;1"          },  // Code (interpreted) (Tool Command Language)
  {"r",                   "38;5;49"            },  // Code (interpreted) (R)
  {"R",                   "38;5;49"            },  // Code (interpreted) (R)
  {"gs",                  "38;5;81"            },  // GrADS
  {"clj",                 "38;5;41"            },  // Clojure
  {"cljs",                "38;5;41"            },  // Clojure
  {"cljc",                "38;5;41"            },  // Clojure
  {"cljw",                "38;5;41"            },  // Clojure Gorilla notebook
  {"scala",               "38;5;41"            },  // Scala
  {"sc",                  "38;5;41"            },  // Scala
  {"dart",                "38;5;51"            },  // Dart
  {"asm",                 "38;5;81"            },  // ASM
  {"cl",                  "38;5;81"            },  // LISP
  {"ml",                  "38;5;81"            },  // LISP
  {"lisp",                "38;5;81"            },  // LISP
  {"rkt",                 "38;5;81"            },  // LISP
  {"el",                  "38;5;81"            },  // LISP (Emacs)
  {"elc",                 "38;5;241"           },  // LISP (Emacs)
  {"eln",                 "38;5;241"           },  // LISP (Emacs)
  {"lua",                 "38;5;81"            },  // Code (interpreted) (Lua)
  {"moon",                "38;5;81"            },  // Code (interpreted) (Moonscript)
  {"c",                   "38;5;81"            },  // C
  {"C",                   "38;5;81"            },  // C
  {"h",                   "38;5;110"           },  // C headers
  {"H",                   "38;5;110"           },  // C headers
  {"tcc",                 "38;5;110"           },  // C headers
  {"c++",                 "38;5;81"            },  // C++
  {"h++",                 "38;5;110"           },  // C++ headers
  {"hpp",                 "38;5;110"           },  // C++ headers
  {"hxx",                 "38;5;110"           },  // C++ headers
  {"ii",                  "38;5;110"           },  // C++ headers
  {"M",                   "38;5;110"           },  // Objective C method file
  {"m",                   "38;5;110"           },  // Objective C method file
  {"cc",                  "38;5;81"            },  // Csharp
  {"cs",                  "38;5;81"            },  // Csharp
  {"cp",                  "38;5;81"            },  // Csharp
  {"cpp",                 "38;5;81"            },  // Csharp
  {"cxx",                 "38;5;81"            },  // Csharp
  {"cr",                  "38;5;81"            },  // Crystal
  {"go",                  "38;5;81"            },  // Golang
  {"f",                   "38;5;81"            },  // Fortran
  {"F",                   "38;5;81"            },  // Fortran
  {"for",                 "38;5;81"            },  // Fortran
  {"ftn",                 "38;5;81"            },  // Fortran
  {"f90",                 "38;5;81"            },  // Fortran
  {"F90",                 "38;5;81"            },  // Fortran
  {"f95",                 "38;5;81"            },  // Fortran
  {"F95",                 "38;5;81"            },  // Fortran
  {"f03",                 "38;5;81"            },  // Fortran
  {"F03",                 "38;5;81"            },  // Fortran
  {"f08",                 "38;5;81"            },  // Fortran
  {"F08",                 "38;5;81"            },  // Fortran
  {"nim",                 "38;5;81"            },  // Nim
  {"nimble",              "38;5;81"            },  // Nim
  {"s",                   "38;5;110"           },  // Pascal
  {"S",                   "38;5;110"           },  // Pascal
  {"rs",                  "38;5;81"            },  // Code (compiled) (Rust)
  {"scpt",                "38;5;219"           },  // AppleScript
  {"swift",               "38;5;219"           },  // Swift
  {"sx",                  "38;5;81"            },  // SimplexNumerica
  {"vala",                "38;5;81"            },  // Vala
  {"vapi",                "38;5;81"            },  // Vala
  {"hi",                  "38;5;110"           },  // Haskell
  {"hs",                  "38;5;81"            },  // Haskell
  {"lhs",                 "38;5;81"            },  // Haskell
  {"agda",                "38;5;81"            },  // Agda
  {"lagda",               "38;5;81"            },  // Agda
  {"lagda.tex",           "38;5;81"            },  // Agda
  {"lagda.rst",           "38;5;81"            },  // Agda
  {"lagda.md",            "38;5;81"            },  // Agda
  {"agdai",               "38;5;110"           },  // Agda
  {"zig",                 "38;5;81"            },  // Zig
  {"v",                   "38;5;81"            },  // V
  {"rego",                "38;5;178"           },  // Code (Rego)
  {"pyc",                 "38;5;240"           },  // Code (Python)
  {"tf",                  "38;5;168"           },  // Code (Terraform)
  {"tfstate",             "38;5;168"           },  // Code (Terraform)
  {"tfvars",              "38;5;168"           },  // Code (Terraform)
  {"http",                "38;5;90;1"          },  // Request (Web)
  {"eml",                 "38;5;90;1"          },  // Email (Web)
  {"css",                 "38;5;105;1"         },  // Styling (Web)
  {"less",                "38;5;105;1"         },  // Styling (Web)
  {"sass",                "38;5;105;1"         },  // Styling (Web)
  {"scss",                "38;5;105;1"         },  // Styling (Web)
  {"htm",                 "38;5;125;1"         },  // Styling (Web)
  {"html",                "38;5;125;1"         },  // Markup (Web)
  {"jhtm",                "38;5;125;1"         },  // Markup (Web)
  {"mht",                 "38;5;125;1"         },  // Markup (Web)
  {"mustache",            "38;5;135;1"         },  // Templating (Web)
  {"ejs",                 "38;5;135;1"         },  // Templating (Web)
  {"pug",                 "38;5;135;1"         },  // Templating (Web)
  {"svelte",              "38;5;135;1"         },  // Templating (Web)
  {"vue",                 "38;5;135;1"         },  // Templating (Web)
  {"astro",               "38;5;135;1"         },  // Templating (Web)
  {"js",                  "38;5;074;1"         },  // Javascript
  {"jsx",                 "38;5;074;1"         },  // Javascript eXtended
  {"ts",                  "38;5;074;1"         },  // Typescript
  {"tsx",                 "38;5;074;1"         },  // Typescript eXtended
  {"mjs",                 "38;5;074;1"         },  // ECMAScript
  {"cjs",                 "38;5;074;1"         },  // CommonJS
  {"coffee",              "38;5;079;1"         },  // Java
  {"java",                "38;5;079;1"         },  // Java
  {"jsm",                 "38;5;079;1"         },  // Java
  {"jsp",                 "38;5;079;1"         },  // Java
  {"php",                 "38;5;81"            },  // php
  {"ctp",                 "38;5;81"            },  // php (CakePHP)
  {"twig",                "38;5;81"            },  // php (Twig)
  {"vb",                  "38;5;81"            },  // VBA
  {"vba",                 "38;5;81"            },  // VBA
  {"vbs",                 "38;5;81"            },  // VBA
  {"containerignore",     "38;5;240"           },  // Build process // Containers
  {"dockerignore",        "38;5;240"           },  // Build process (Docker)
  {"nix",                 "38;5;155"           },  // Functional configuration
  {"dhall",               "38;5;178"           },  // Functional configuration
  {"rake",                "38;5;155"           },  // Build process (Ruby)
  {"am",                  "38;5;242"           },  // Build process (Automake)
  {"in",                  "38;5;242"           },  // Build process (Automake)
  {"hin",                 "38;5;242"           },  // Build process (Automake)
  {"scan",                "38;5;242"           },  // Build process (Automake)
  {"m4",                  "38;5;242"           },  // Build process (Automake)
  {"old",                 "38;5;242"           },  // Build process (Automake)
  {"out",                 "38;5;242"           },  // Build process (Automake)
  {"SKIP",                "38;5;244"           },  // Build process (Automake)
  {"diff",                "48;5;197;38;5;232"  },  // Patch files
  {"patch",               "48;5;197;38;5;232;1"},  // Patch files
  {"bmp",                 "38;5;97"            },  // Graphics
  {"dicom",               "38;5;97"            },  // Graphics
  {"tiff",                "38;5;97"            },  // Graphics
  {"tif",                 "38;5;97"            },  // Graphics
  {"TIFF",                "38;5;97"            },  // Graphics
  {"cdr",                 "38;5;97"            },  // Graphics
  {"flif",                "38;5;97"            },  // Graphics
  {"gif",                 "38;5;97"            },  // Graphics
  {"icns",                "38;5;97"            },  // Graphics
  {"ico",                 "38;5;97"            },  // Graphics
  {"jpeg",                "38;5;97"            },  // Graphics
  {"JPG",                 "38;5;97"            },  // Graphics
  {"jpg",                 "38;5;97"            },  // Graphics
  {"jxl",                 "38;5;97"            },  // Graphics
  {"nth",                 "38;5;97"            },  // Graphics
  {"png",                 "38;5;97"            },  // Graphics
  {"psd",                 "38;5;97"            },  // Graphics
  {"pxd",                 "38;5;97"            },  // Graphics
  {"pxm",                 "38;5;97"            },  // Graphics
  {"xpm",                 "38;5;97"            },  // Graphics
  {"webp",                "38;5;97"            },  // Graphics
  {"ai",                  "38;5;99"            },  // Graphics (Vector)
  {"eps",                 "38;5;99"            },  // Graphics (Vector)
  {"epsf",                "38;5;99"            },  // Graphics (Vector)
  {"drw",                 "38;5;99"            },  // Graphics (Vector)
  {"ps",                  "38;5;99"            },  // Graphics (Vector)
  {"svg",                 "38;5;99"            },  // Graphics (Vector)
  {"avi",                 "38;5;114"           },  // Video
  {"divx",                "38;5;114"           },  // Video
  {"IFO",                 "38;5;114"           },  // Video
  {"m2v",                 "38;5;114"           },  // Video
  {"m4v",                 "38;5;114"           },  // Video
  {"mkv",                 "38;5;114"           },  // Video
  {"MOV",                 "38;5;114"           },  // Video
  {"mov",                 "38;5;114"           },  // Video
  {"mp4",                 "38;5;114"           },  // Video
  {"mpeg",                "38;5;114"           },  // Video
  {"mpg",                 "38;5;114"           },  // Video
  {"ogm",                 "38;5;114"           },  // Video
  {"rmvb",                "38;5;114"           },  // Video
  {"sample",              "38;5;114"           },  // Video
  {"wmv",                 "38;5;114"           },  // Video
  {"3g2",                 "38;5;115"           },  // Video (mobile/streaming)
  {"3gp",                 "38;5;115"           },  // Video (mobile/streaming)
  {"gp3",                 "38;5;115"           },  // Video (mobile/streaming)
  {"webm",                "38;5;115"           },  // Video (mobile/streaming)
  {"gp4",                 "38;5;115"           },  // Video (mobile/streaming)
  {"asf",                 "38;5;115"           },  // Video (mobile/streaming)
  {"flv",                 "38;5;115"           },  // Video (mobile/streaming)
  {"ogv",                 "38;5;115"           },  // Video (mobile/streaming)
  {"f4v",                 "38;5;115"           },  // Video (mobile/streaming)
  {"VOB",                 "38;5;115;1"         },  // Video (lossless)
  {"vob",                 "38;5;115;1"         },  // Video (lossless)
  {"ass",                 "38;5;117"           },  // Subtitles
  {"srt",                 "38;5;117"           },  // Subtitles
  {"ssa",                 "38;5;117"           },  // Subtitles
  {"sub",                 "38;5;117"           },  // Subtitles
  {"sup",                 "38;5;117"           },  // Subtitles
  {"vtt",                 "38;5;117"           },  // Subtitles
  {"3ga",                 "38;5;137;1"         },  // Audio (lossy)
  {"S3M",                 "38;5;137;1"         },  // Audio (lossy)
  {"aac",                 "38;5;137;1"         },  // Audio (lossy)
  {"amr",                 "38;5;137;1"         },  // Audio (lossy)
  {"au",                  "38;5;137;1"         },  // Audio (lossy)
  {"caf",                 "38;5;137;1"         },  // Audio (lossy)
  {"dat",                 "38;5;137;1"         },  // Audio (lossy)
  {"dts",                 "38;5;137;1"         },  // Audio (lossy)
  {"fcm",                 "38;5;137;1"         },  // Audio (lossy)
  {"m4a",                 "38;5;137;1"         },  // Audio (lossy)
  {"mod",                 "38;5;137;1"         },  // Audio (lossy)
  {"mp3",                 "38;5;137;1"         },  // Audio (lossy)
  {"mp4a",                "38;5;137;1"         },  // Audio (lossy)
  {"oga",                 "38;5;137;1"         },  // Audio (lossy)
  {"ogg",                 "38;5;137;1"         },  // Audio (lossy)
  {"opus",                "38;5;137;1"         },  // Audio (lossy)
  {"s3m",                 "38;5;137;1"         },  // Audio (lossy)
  {"sid",                 "38;5;137;1"         },  // Audio (lossy)
  {"wma",                 "38;5;137;1"         },  // Audio (lossy)
  {"ape",                 "38;5;136;1"         },  // Audio (lossless)
  {"aiff",                "38;5;136;1"         },  // Audio (lossless)
  {"cda",                 "38;5;136;1"         },  // Audio (lossless)
  {"flac",                "38;5;136;1"         },  // Audio (lossless)
  {"alac",                "38;5;136;1"         },  // Audio (lossless)
  {"mid",                 "38;5;136;1"         },  // Audio (lossless)
  {"midi",                "38;5;136;1"         },  // Audio (lossless)
  {"pcm",                 "38;5;136;1"         },  // Audio (lossless)
  {"wav",                 "38;5;136;1"         },  // Audio (lossless)
  {"wv",                  "38;5;136;1"         },  // Audio (lossless)
  {"wvc",                 "38;5;136;1"         },  // Audio (lossless)
  {"afm",                 "38;5;66"            },  // Fonts
  {"fon",                 "38;5;66"            },  // Fonts
  {"fnt",                 "38;5;66"            },  // Fonts
  {"pfb",                 "38;5;66"            },  // Fonts
  {"pfm",                 "38;5;66"            },  // Fonts
  {"ttf",                 "38;5;66"            },  // Fonts
  {"otf",                 "38;5;66"            },  // Fonts
  {"woff",                "38;5;66"            },  // Fonts
  {"woff2",               "38;5;66"            },  // Fonts
  {"PFA",                 "38;5;66"            },  // Fonts
  {"pfa",                 "38;5;66"            },  // Fonts
  {"apk",                 "38;5;215"           },  // Packaged apps
  {"ipa",                 "38;5;215"           },  // Packaged apps
  {"deb",                 "38;5;215"           },  // Packaged apps
  {"rpm",                 "38;5;215"           },  // Packaged apps
  {"jad",                 "38;5;215"           },  // Packaged apps
  {"jar",                 "38;5;215"           },  // Packaged apps
  {"ear",                 "38;5;215"           },  // Packaged apps
  {"war",                 "38;5;215"           },  // Packaged apps
  {"cab",                 "38;5;215"           },  // Packaged apps
  {"pak",                 "38;5;215"           },  // Packaged apps
  {"pk3",                 "38;5;215"           },  // Packaged apps
  {"vdf",                 "38;5;215"           },  // Packaged apps
  {"vpk",                 "38;5;215"           },  // Packaged apps
  {"bsp",                 "38;5;215"           },  // Packaged apps
  {"dmg",                 "38;5;215"           },  // Packaged apps
  {"crx",                 "38;5;215"           },  // Packaged apps // Google Chrome extension
  {"xpi",                 "38;5;215"           },  // Packaged apps // Mozilla Firefox extension
  {"iso",                 "38;5;124"           },  // Partition images
  {"img",                 "38;5;124"           },  // Partition images
  {"bin",                 "38;5;124"           },  // Partition images
  {"nrg",                 "38;5;124"           },  // Partition images
  {"qcow",                "38;5;124"           },  // Partition images
  {"fvd",                 "38;5;124"           },  // Partition images
  {"sparseimage",         "38;5;124"           },  // Partition images
  {"toast",               "38;5;124"           },  // Partition images
  {"vcd",                 "38;5;124"           },  // Partition images
  {"vdi",                 "38;5;124"           },  // Partition images
  {"vhd",                 "38;5;124"           },  // Partition images
  {"vhdx",                "38;5;124"           },  // Partition images
  {"vfd",                 "38;5;124"           },  // Partition images
  {"vmdk",                "38;5;124"           },  // Partition images
  {"swp",                 "38;5;244"           },  // Temporary files
  {"swo",                 "38;5;244"           },  // Temporary files
  {"tmp",                 "38;5;244"           },  // Temporary files
  {"sassc",               "38;5;244"           },  // Temporary files
  {"pacnew",              "38;5;33"            },  // Undo files
  {"un~",                 "38;5;241"           },  // Undo files
  {"orig",                "38;5;241"           },  // Undo files
  {"BUP",                 "38;5;241"           },  // Backups
  {"bak",                 "38;5;241"           },  // Backups
  {"o",                   "38;5;241"           },  // *nix Object file (shared libraries, core dumps etc)
  {"mdump",               "38;5;241"           },  // Mini DuMP crash report
  {"rlib",                "38;5;241"           },  // Static rust library
  {"dll",                 "38;5;241"           },  // dynamic linked library
  {"aria2",               "38;5;241"           },  // state dumps
  {"dump",                "38;5;241"           },  // state dumps
  {"stackdump",           "38;5;241"           },  // state dumps
  {"zcompdump",           "38;5;241"           },  // state dumps
  {"zwc",                 "38;5;241"           },  // state dumps
  {"part",                "38;5;239"           },  // Partial files
  {"pid",                 "38;5;248"           },  // state files
  {"state",               "38;5;248"           },  // state files
  {"err",                 "38;5;160;1"         },  // error logs
  {"error",               "38;5;160;1"         },  // error logs
  {"stderr",              "38;5;160;1"         },  // error logs
  {"pcap",                "38;5;29"            },  // tcpdump / network traffic capture
  {"cap",                 "38;5;29"            },  // tcpdump / network traffic capture
  {"dmp",                 "38;5;29"            },  // tcpdump / network traffic capture
  {"allow",               "38;5;112"           },  // /etc/hosts
  {"deny",                "38;5;196"           },  // /etc/hosts
  {"service",             "38;5;45"            },  // systemd
  {"socket",              "38;5;45"            },  // systemd
  {"swap",                "38;5;45"            },  // systemd
  {"device",              "38;5;45"            },  // systemd
  {"mount",               "38;5;45"            },  // systemd
  {"automount",           "38;5;45"            },  // systemd
  {"target",              "38;5;45"            },  // systemd
  {"path",                "38;5;45"            },  // systemd
  {"timer",               "38;5;45"            },  // systemd
  {"snapshot",            "38;5;45"            },  // systemd
  {"lnk",                 "38;5;39"            },  // windows symlink
  {"application",         "38;5;116"           },  // metadata
  {"cue",                 "38;5;116"           },  // metadata
  {"description",         "38;5;116"           },  // metadata
  {"directory",           "38;5;116"           },  // metadata
  {"m3u",                 "38;5;116"           },  // metadata
  {"m3u8",                "38;5;116"           },  // metadata
  {"md5",                 "38;5;116"           },  // metadata
  {"properties",          "38;5;116"           },  // metadata
  {"sfv",                 "38;5;116"           },  // metadata
  {"theme",               "38;5;116"           },  // metadata
  {"torrent",             "38;5;116"           },  // metadata
  {"urlview",             "38;5;116"           },  // metadata
  {"webloc",              "38;5;116"           },  // metadata
  {"asc",                 "38;5;192;3"         },  // Encrypted data
  {"bfe",                 "38;5;192;3"         },  // Encrypted data
  {"enc",                 "38;5;192;3"         },  // Encrypted data
  {"gpg",                 "38;5;192;3"         },  // Encrypted data
  {"signature",           "38;5;192;3"         },  // Encrypted data
  {"sig",                 "38;5;192;3"         },  // Encrypted data
  {"p12",                 "38;5;192;3"         },  // Encrypted data
  {"pem",                 "38;5;192;3"         },  // Encrypted data
  {"pgp",                 "38;5;192;3"         },  // Encrypted data
  {"p7s",                 "38;5;192;3"         },  // Encrypted data
  {"32x",                 "38;5;213"           },  // Game console emulation
  {"cdi",                 "38;5;213"           },  // Game console emulation
  {"fm2",                 "38;5;213"           },  // Game console emulation
  {"rom",                 "38;5;213"           },  // Game console emulation
  {"sav",                 "38;5;213"           },  // Game console emulation
  {"st",                  "38;5;213"           },  // Game console emulation
  {"a00",                 "38;5;213"           },  // Game console emulation // Atari
  {"a52",                 "38;5;213"           },  // Game console emulation // Atari
  {"A64",                 "38;5;213"           },  // Game console emulation // Atari
  {"a64",                 "38;5;213"           },  // Game console emulation // Atari
  {"a78",                 "38;5;213"           },  // Game console emulation // Atari
  {"adf",                 "38;5;213"           },  // Game console emulation // Atari
  {"atr",                 "38;5;213"           },  // Game console emulation // Atari
  {"gb",                  "38;5;213"           },  // Game console emulation // Nintendo
  {"gba",                 "38;5;213"           },  // Game console emulation // Nintendo
  {"gbc",                 "38;5;213"           },  // Game console emulation // Nintendo
  {"gel",                 "38;5;213"           },  // Game console emulation // Nintendo
  {"gg",                  "38;5;213"           },  // Game console emulation // Nintendo
  {"ggl",                 "38;5;213"           },  // Game console emulation // Nintendo
  {"ipk",                 "38;5;213"           },  // Game console emulation // Nintendo DS Packed Images
  {"j64",                 "38;5;213"           },  // Game console emulation // Nintendo
  {"nds",                 "38;5;213"           },  // Game console emulation // Nintendo
  {"nes",                 "38;5;213"           },  // Game console emulation // Nintendo NES
  {"sms",                 "38;5;213"           },  // Sega
  {"8xp",                 "38;5;121"           },  // Texas Instruments Calculator files
  {"8eu",                 "38;5;121"           },  // Texas Instruments Calculator files
  {"82p",                 "38;5;121"           },  // Texas Instruments Calculator files
  {"83p",                 "38;5;121"           },  // Texas Instruments Calculator files
  {"8xe",                 "38;5;121"           },  // Texas Instruments Calculator files
  {"stl",                 "38;5;216"           },  // 3D printing
  {"dwg",                 "38;5;216"           },  // 3D printing
  {"ply",                 "38;5;216"           },  // 3D printing
  {"wrl",                 "38;5;216"           },  // 3D printing
  {"vert",                "38;5;136"           },  // SPIR-V shaders
  {"comp",                "38;5;136"           },  // SPIR-V shaders
  {"frag",                "38;5;136"           },  // SPIR-V shaders
  {"spv",                 "38;5;217"           },  // SPIR-V compiled shaders
  {"wgsl",                "38;5;97"            },  // WGSL shaders
  {"xib",                 "38;5;208"           },  
  {"iml",                 "38;5;166"           },  // AppCode files
  {"DS_Store",            "38;5;239"           },  // macOS
  {"localized",           "38;5;239"           },  // macOS
  {"CFUserTextEncoding",  "38;5;239"           },  // macOS
  {"nib",                 "38;5;57"            },  // macOS UI
  {"car",                 "38;5;57"            },  // macOS asset catalog
  {"dylib",               "38;5;241"           },  // macOS shared lib
  {"entitlements",        "1"                  },  // Xcode files
  {"pbxproj",             "1"                  },  // Xcode files
  {"strings",             "1"                  },  // Xcode files
  {"storyboard",          "38;5;196"           },  // Xcode files
  {"xcconfig",            "1"                  },  // Xcode files
  {"xcsettings",          "1"                  },  // Xcode files
  {"xcuserstate",         "1"                  },  // Xcode files
  {"xcworkspacedata",     "1"                  },  // Xcode files
  {"pot",                 "38;5;7"             },  
  {"pcb",                 "38;5;7"             },  
  {"mm",                  "38;5;7"             },  
  {"gbr",                 "38;5;7"             },  
  {"scm",                 "38;5;7"             },  
  {"xcf",                 "38;5;7"             },  
  {"spl",                 "38;5;7"             },  
  {"Rproj",               "38;5;11"            },  
  {"sis",                 "38;5;7"             },  
  {"1p",                  "38;5;7"             },  
  {"3p",                  "38;5;7"             },  
  {"cnc",                 "38;5;7"             },  
  {"def",                 "38;5;7"             },  
  {"ex",                  "38;5;7"             },  
  {"example",             "38;5;7"             },  
  {"feature",             "38;5;7"             },  
  {"ger",                 "38;5;7"             },  
  {"ics",                 "38;5;7"             },  // calendar information
  {"map",                 "38;5;7"             },  
  {"mf",                  "38;5;7"             },  
  {"mfasl",               "38;5;7"             },  
  {"mi",                  "38;5;7"             },  
  {"mtx",                 "38;5;7"             },  
  {"pc",                  "38;5;7"             },  
  {"pi",                  "38;5;7"             },  
  {"plt",                 "38;5;7"             },  
  {"rdf",                 "38;5;7"             },  
  {"ru",                  "38;5;7"             },  
  {"sch",                 "38;5;7"             },  
  {"sty",                 "38;5;7"             },  
  {"sug",                 "38;5;7"             },  
  {"tdy",                 "38;5;7"             },  
  {"tfm",                 "38;5;7"             },  
  {"tfnt",                "38;5;7"             },  
  {"tg",                  "38;5;7"             },  
  {"vcard",               "38;5;7"             },  // contact information
  {"vcf",                 "38;5;7"             },  // contact information
  {"xln",                 "38;5;7"             },  

// manual entries
  {"cu",                  "38;5;42"            },  // CUDA
  {"conf",                "38;5;243"           },  // config files

// default
  {"EXEC",                "38;5;208;1"         },  // core
  {"",                    "0"                  },  
};
#define sizeof_color_list  (sizeof(color_list)/sizeof(*color_list) - 2ULL)
#define COLOR_EXEC         (sizeof(color_list)/sizeof(*color_list) - 2ULL)
#define COLOR_DEFAULT      (sizeof(color_list)/sizeof(*color_list) - 1ULL)

#endif //_COLOR_LIST_H_
