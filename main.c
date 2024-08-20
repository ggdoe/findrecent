#include "defs.h"

// #define BENCH_PRECISION µs
// #define BENCH_LOG_SIZE 1
// #include "bench.h"

struct parsed_options
{
  struct options options;
  char *main_directory;
};

struct parsed_options parse_options(int argc, char** argv)
{
  static char local_directory[NAME_MAX] = ".";
  char* main_directory = local_directory;
  if(argc>1) main_directory = argv[1];

  omp_set_num_threads(3); // 3 best ?

  struct options options;
  options.date_type = DATE_MODIF;
  // options.date_type = DATE_CREAT;
  // options.date_type = DATE_ACCESS;
  options.search_type = SEARCH_FILES;
  // options.search_type = SEARCH_DIRECTORIES;

  return (struct parsed_options){
    .options=options, 
    .main_directory=main_directory
    };
}

//TODO:
/*
  depth, fzf
  exclude_path : prise en compte de * pour match plusieurs caractères
  exclude_path via fichier config : .config/findrecent/exclude ?

  .git                exclure tous les dossier .git
  .git/               idem
  build/.git          exclure les .git qui sont inclus dans un dossier build
  ./build             exclure le fichier build à la racine du main_directory
  /home/neko/.config  exclure le fichier /home/neko/.config mais pas les autres .config

stratégie pour exclude les paths:
  a1/a2/a3/file1
  b1/b2/b3/file2
  c1/c2/c3/file3

struct path_to_exclude {
  char *first_path;
  char *cur_path;
}

first_path pointe sur une strings contenant les premiers répertoire à vérifier, accoler au ptr vers les répertoires suivant :
first_path    --> a1 \0 `ptr vers a2` \0 b1 \0 `ptr vers b2` \0 c1 \0 `ptr vers c2` \0 
`ptr vers a2` --> a2 \0 a3 \0 file1 \0 \0
`ptr vers b2` --> b2 \0 b3 \0 file2 \0 \0
`ptr vers b2` --> c2 \0 c3 \0 file3 \0 \0

le nom du prochain répertoire est à chaque fois délimité par un \0
si le nom est \0, on est arrivé au bout de la liste, par conséquant le dossier est à exclure et on ne l'explorera pas

à chaque étape on doit vérifier qu'on n'est dans aucun dossier contenu dans first_path
si on match un dossier de first_path, alors cur_path pointe vers `ptr vers X2`, et au prochain tour on doit vérifier aussi si le répertoire match cur_path
si ça ne match pas alors on remet cur_path par défaut et on ne vérifie plus s'il match.
*/

//BUGS:
  // quand il y a trop de threads, possibilité de dépasser le nombre maximum de file descriptor ouvert (généralement 1024) --> crash



int main(int argc, char** argv)
{
  // char cwd[256];
  // getcwd(cwd, 256);
  struct parsed_options parsed = parse_options(argc, argv);

  // BENCH_BENCH(BENCH_LOG_SIZE,
  // BENCH_START;
  struct list_entries l = findrecent(parsed.main_directory, &parsed.options);
  // BENCH_LOG;
  // BENCH_PRINT;
  // findrecent("/home/elrond");
  // );
  // BENCH_PRINT

  print_list_entry(&l, true);  
  free_list_entries(&l);
  return 0;
}
