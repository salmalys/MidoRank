#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include "wiki.h"

//A ajouter dans la bibil wiki

void affiche_podium(x, Vec, n){
  for(int j = 0; j<x; j++){
    int max = 0; 
    for(int i = 1; i<n+1; i++){
      if (Vec[i].pageRank > max)
        max = i;
    }
    printf("%d : %s PageRank = %lf", j, Vec[max].name, Vec[max].pageRank);
    Vec[max].pageRank = -1;
  }
}

void algorithm(FILE* f, List Adj, int n){
  read_link(Adj, file);
  wiki(file,Adj,n);
  fclose(file);
  //print_graph(Adj, n);
  
  List Adj_pred[n+1];
  pred(Adj, Adj_pred,n);
  
  Page* Vec = start(Adj, n);
  long double E1;
  E1 = (long double)1/(10*n);
  
  int k = 1;
  while (k--)
    update(Vec, Adj, Adj_pred, n, E);
  
  affiche_podium(x, Vex, n);
}


int main(int argc, char *argv[]){
  if (strcmp(argv[1],"-t") == 0){
    char* value = argv[2];
    int k = atoi(value);

    char* tab_files[6]= {"alea4-6.txt", "alea4-12.txt","alea10-40.txt","alea50-1000.txt","alea100-5000.txt","alea1000-10000.txt"};

    for (int i = 0; i<1; i++){
      FILE* file = fopen(tab_files[i], "r");
      if (file == NULL){
        printf("File not found");
        exit(0);
      }
      experience(file, k);
    }
  }
  
  if (strcmp(argv[1],"-n") == 0){
    FILE* file = fopen(argv[2], "r");
    if (file == NULL){
        printf("File not found");
        exit(0);
      }
    char* value = argv[3];
    int x = atoi(value);
    
    int n = number_lines(file);
    List Adj[n+1];
    algorithm(file, Adj, n, x);
    
  }
  return 0;
}
