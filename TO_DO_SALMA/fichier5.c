#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"


int main(int argc, char *argv[]){

    FILE* f = fopen(argv[1],"r");
    if(f == NULL) {
      printf("File not found");
      return 0;
    }

    int n = size_matrix(f);
    fclose(f);

    List Adj[n+1];

    FILE* f1 = fopen(argv[1],"r");
    if(f1 == NULL) return 0;
    graph_init_mat(f1,Adj,n);
    //print_graph(Adj,n);

    List Adj_pred[n+1];
    pred(Adj, Adj_pred,n);

    Page* Vec = start(Adj, n);
    int k = 100;
    long double E;
    E = (long double)1/(10*n);

    while (k--)
      update(Vec, Adj, Adj_pred, n, E);

    affiche_res(Vec,n);

    return 0;
}
