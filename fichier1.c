#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include"wiki.h"


int main(int argc, char *argv[]){

  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
      printf("File not found\n");
      return 0;
  }


  int n = number_lines(file);
  List Adj[n+1];

  read_link(Adj, file);
  //print_graph(Adj, n);
  wiki(file,Adj,n);
  fclose(file);
  print_graph(Adj, n);


    return 0;
}
