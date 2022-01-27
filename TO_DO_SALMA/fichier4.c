#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include "wiki.h"


int main(int argc, char *argv[]){
  if (strcmp(argv[1],"-t") == 0){
    char* value = argv[2];
    int k = atoi(value);

    char* tab_files[6]= {"alea4-6.txt", "alea4-12.txt","alea10-40.txt","alea50-1000.txt","alea100-5000.txt","alea1000-10000.txt"};

    for (int i = 0; i<1; i++){
      printf("Matrice du fichier %s\n", tab_files[i]);
      experience(tab_files[i], k);
    }
  }

  else if (strcmp(argv[1],"-n") == 0){
    FILE* file = fopen(argv[2], "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }

    char* value = argv[3];
    int x = atoi(value);

    int n = number_lines(file);
    List Adj[n+1];

    algorithm(file,x, Adj, n);
  }
  else {
    printf("Veuillez consulter la notice READ ME\n");
  }

  return 0;
}
