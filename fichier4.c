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
      experience(tab_files[i], k);
    }
  }
  if (strcmp(argv[1],"-n") == 0){
    FILE* file = fopen(argv[1], "r");
    int n = number_lines(file);
    List Adj[n+1];

    read_link(Adj, file);
    wiki(file,Adj,n);
    fclose(file);
    print_graph(Adj, n);
  }
  return 0;
}
