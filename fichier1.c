#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include"wiki.h"


void affiche_podium(int x, Page* Vec, int n){
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

void algorithm(FILE* file, int x, List Adj[], int n){
  read_link(Adj, file);
  wiki(file,Adj,n);
  fclose(file);
  print_graph(Adj, n);

  List Adj_pred[n+1];
  pred(Adj, Adj_pred,n);

  Page* Vec = start(Adj, n);
  long double E;
  E = (long double)1/(10*n);

  int k = 1;
  while (k--)
    update(Vec, Adj, Adj_pred, n, E);

  affiche_podium(x, Vec, n);
}

int main(int argc, char *argv[]){

  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
      printf("File not found\n");
      return 0;
  }

  char* value = argv[2];
  int x = atoi(value);

  int n = number_lines(file);
  List Adj[n+1];

  //algorithm(file,x, Adj, n);

  return 0;
}
