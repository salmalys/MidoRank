#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"

//A traiter
int number_lines(char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }
    int n = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)){
      n++;
    }
    fclose(file);
    return n;
}


int test_in_list(List* l, char* name){
    if (l->first == NULL) return 0;
    Node* s = l->first;
    while(s){
        if (strcmp(s->name,name)==0) return 1;
        s = s->next;
    }
    return 0;
}

int test_red_link(char* name, List Adj[], int n){
  for(int i = 0; i<n+1; i++){
    if (strcmp(Adj[i].name, name) == 0)
      return 1;
  }
  return 0;
}



/*List* list_init1(char* line){
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

void read_line(FILE* f, List Adj[], int n){
  char line[256];
  while (fgets(line, 256, f)){
    List* l = list_init(line);
    print_list(l);
  }
}*/

void graph(List Adj[]){
  Adj[0] = *(list_init("SuperNode"));
  Adj[1] = *(list_init("page1"));
  Adj[2] = *(list_init("page2"));
  Adj[3] = *(list_init("page3"));
}

void read_link(List Adj[], FILE* f){//permet de récuperer le nb de lignes
  Adj[0] = *(list_init("SuperNode"));
  int j = 0;
  char* line = malloc(sizeof(char*));
  while (fgets(line, 256, f)){
  //printf("%s",line);
   char* name=malloc(sizeof(char*));
    int i = 0;
    while ((*(line)!= '|')&&(*(line)!= '\n')){
      name[i++] = *(line++);
    }
      j++;
   Adj[j] = *(list_init(name));
   add_list(&Adj[j],name);    //s'ajoute lui meme
   add_list(&Adj[j],"SuperNode");
   add_list(&Adj[0], name);

  }
  rewind(f);

}

int test(char* name, List* l, List Adj[], int n){
  if (test_in_list(l,name) == 0) //test si il a pas été déjà ajouter dans la liste
    return 1;
  if (test_red_link(name, Adj, n)== 1)
    return 1;
  return 0;
}

void wiki_aux(char* line, List* list, List Adj[], int n){
  while (*line != '|')
    line++; // Boucle pour venir sur la première page

  while(*line != '\n'){
    line++;
    char* name = malloc(sizeof(char*));
    int i = 0;
    while ((*line != '|')&&(*line != '\n')){
      name[i++] = *(line++);
    }

    if (test(name, list, Adj, n)){
      add_list(list,name);
      list->cpt_sort++;
    }
  }
  print_list(list);
  exit(0);
}

void wiki(List Adj[], FILE *f, int n){
  for (int i = 1; i<n+1; i++){
    char* line = malloc(sizeof(char*));
    fgets(line, 256, f);
    //fgets(line, 256, f);
    printf("%s\n", line);
    //wiki_aux(line, &Adj[i], Adj, n);
  }
}


int main(int argc, char *argv[]){
    //int n = number_lines(argv[1]);
    int n = 3;
    List Adj[n+1];

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File not found\n");
        return 0;
    }

    read_link(Adj, file);
    wiki(Adj, file, n);
    //print_graph(Adj, n);


    //read_link(Adj, file);

    //print_graph(Adj, n);
    /*read_line(file, Adj, n);
    fclose(file);

    print_graph(Adj, n);

    Page* Vec = start(Adj, n);
    int k = 100;
    float E;
    E = (float)1/(10*n);

    while (k--)
        update(Vec, Adj, n, E);

    affiche_res(Vec,n);*/

    return 0;
}
