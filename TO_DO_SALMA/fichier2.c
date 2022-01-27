#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"

//fichier2 recopie du fichier1


List* read_line(char* filename, int* n){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found\n");
        return;
    }
    List Adj[] = malloc(sizeof(List)*N);
    Adj[0]->name = "SuperNode";
    Ajd[0]->first = NULL;
  char* line = malloc(sizeof(char*));
    int i = 1;
  while (fgets(line, sizeof(line), file)){
        (*n)++;
    List* l = list_init(line, Adj[0]);
        Adj[i++] = l;
      print_list(l);
  }
  fclose(file);
    return Adj;
}


int main(int argc, char* argv[]){
    //Paramètres:
    int k = 100; //nombre de fois de la mise à jour
    double E; //possibilité de le faire choisir à l'utilisateur

    int n = 0; //le nombre de pages (=nombre de lignes dans le fichier)
  List Adj[] = read_line(argv[1], &n);
    Page* Vec = start(Adj, n);

    E = 1/(10*n);
    while (k--)
        update(Vec, Adj, n, E);

    affichage_res(Vec, n);
  return 0;
}
