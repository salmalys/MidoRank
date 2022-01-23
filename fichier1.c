#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"

int number_lines(char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }
    int n = 0;
    char line[256];
  while (fgets(line, sizeof(line), file))
        n++;
    return n;
    fclose(file);
}


int test_in(List* l, char* name){
    if (l->first == NULL) return 0;
    Node* s = l->first;
    while(s){
        if (strcmp(s->name,name)==0) return 1;
        s = s->next;
    }
    return 0;
}


List* list_init(char* line){
  List *l= malloc(sizeof(List));
  if (l == NULL) return NULL;
  char* name = malloc(sizeof(char*));
  int i = 0;
  while (*(line)!= '|'){
    name[i++] = *(line++);
  }
  l->name = name;
  l->first = NULL;
  while(*(line)!= '\n'){
    char* page = malloc(sizeof(char*));
    int j = 0;
        line++;
    while (*(line)!= '\n'&&*(line)!= '|'){
      page[j++] = *(line);
            line++;
    }
        if (test_in(l,page) == 0) {
            if (strcmp(page,name)!= 0)
            add_list(l,page);
        }
  }
    add_list(l,"SuperNode");
    add_list(l,name);
  return l;
}

void read_line(FILE* file, List Adj[], int n){
    Adj[0].name = "SuperNode";
    Adj[0].first = NULL;
    int i = 1;
  char line[256];
  while (fgets(line, sizeof(line), file)){
    List* l = list_init(line);
        Adj[i] = *l;
        add_list(&Adj[0],Adj[i].name);
        i++;
  }
}


int main(int argc, char *argv[]){
    int n = number_lines(argv[1]);
    List Adj[n+1];

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }
    read_line(file, Adj, n);
    fclose(file);

    print_graph(Adj, n);

    Page* Vec = start(Adj, n);
    int k = 100;
    float E;
    E = (float)1/(10*n);

    while (k--)
        update(Vec, Adj, n, E);

    affiche_res(Vec,n);

    return 0;
}
