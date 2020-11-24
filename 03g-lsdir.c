#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

// Beenden mit Fehlermeldung
void die(const char *msg) {
  perror(msg);
  exit(1);
}

#define TRUE 1

char working_dir_buffer[128];

// Ausgeben des aktuellen Verzeichnisses
void print_cwd() {
    char buffer[129];
    char *success = getcwd(buffer, 129);
    if(success == NULL){
      die("Getcwd has failed");
    }

    int successPrint = printf("We are at: %s\n", buffer);
    if(successPrint < 1 ){
      die("Print cwd has failed");
    }
}

//Ausgeben des aktuellen Verseichnisses + gegebenen Pfad
void print_path(char *path) {
  print_cwd();
  int charsPrinted = printf("[%s]\n", path);
  if(charsPrinted < 1){
    die("Error while printing the path");
  }
}


// durchlaufen des gegebenen relativen Pfads
void handle_path(char * path) {
  static int current_depth = -1;

  //TODO: implement me
  int success = chdir(path);
  if(success != 0){
    //die("chdir has failed");
    return;
  }

  ++current_depth;
  DIR * dir = opendir(".");
  // opendir, readdir, closedir
  if(!dir){
    die("Opendir has failed");
  }

  struct dirent *current_directory;
  while(TRUE){
      current_directory = readdir(dir);
      if(!current_directory){
        //die("Error while reading directory");
        break;
      }
      if(strcmp(current_directory->d_name, ".") == 0 || strcmp(current_directory->d_name, "..") == 0)
        continue;

      printf("Name:");
      for(size_t i = 0; i < current_depth; ++i)
        printf("  ");

      printf("%s\n", current_directory->d_name);

      handle_path(current_directory->d_name);
  }

  closedir(dir);
  --current_depth;
}


int main(int argc, char *argv[]) {
  if(argc != 2){
      printf("Usage: main DIRPATH\n");
      exit(1);
  }

  print_path(argv[1]);
  handle_path(argv[1]);
  printf("Program finished\n");
}
