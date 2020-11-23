#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#define TRUE 1

const char * pp = "..";
// Beenden mit Fehlermeldung
void die(const char *msg) {
  perror(msg);
  exit(1);
}

char working_dir_buffer[128];

// Ausgeben des aktuellen Verzeichnisses
void print_cwd() {
  char buffer[129];
  char *success = getcwd(buffer, 129);
  if (success == NULL) {
    die("Getcwd failed");
  }

  int success2 = printf("%s", buffer);
  if (success2 < 1) {
    die("Print cwd has failed");
  }
}

//Ausgeben des aktuellen Verseichnisses + gegebenen Pfad
void print_path(char *path) {
  int charsPrinted = printf("%s", path);
  if (charsPrinted == 0) {
    die("Error while printing the path\n");
  }
}


// durchlaufen des gegebenen relativen Pfads
void handle_path(char * path) {
  int success = chdir(path);
  if (success != 0){
    return;
  }

  // opendir, readdir, closedir
  DIR * dir = opendir(".");
  if(!dir) {
    die("Opendir failed");
  }

  struct dirent *current_directory;
  while( (current_directory = readdir(dir)) ){
    if ((strcmp(current_directory->d_name, ".") != 0) && (strcmp(current_directory->d_name, pp) != 0) ) {
      print_cwd();
      printf("/%s\n", current_directory->d_name);
      handle_path(current_directory->d_name);
    }
  }

  closedir(dir);
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: main DIRPATH\n");
    exit(1);
  }

  print_path(argv[1]);
  handle_path(argv[1]);
  printf("Program finished.\n");
}
