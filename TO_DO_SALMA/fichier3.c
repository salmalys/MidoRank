#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"


void read_line(FILE* file){
  char line[256];
  while (fgets(line, sizeof(line), file)){
    List* l = list_init(line);
      print_list(l);
  }
}


int main(int argc, char* argv[]){
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }
    //number_line(file);
  read_line(file);
    fclose(file);
  return 0;
}
