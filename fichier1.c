#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"

//A traiter
int number_lines(FILE* f){
  int n = 0;
  char line[256];
  while (fgets(line, sizeof(line), f))
        n++;
  return n;
  //a modifier si ligne vide !!
}

void read_link(List Adj[], FILE* f){
  rewind(f);
  Adj[0] = *(list_init("SuperNode"));
  int j = 0;
  char* line = malloc(sizeof(char*));
  while (fgets(line, 256, f)){
    char*  name = malloc(sizeof(char*));
    int i = 0;
    while((*line)!= '|'&&(*(line)!= '\n'))
      name[i++] = *(line++);
    j++;
    Adj[j] = *(list_init(name));
    add_list(&Adj[j],name);
    add_list(&Adj[j],"SuperNode");
    add_list(&Adj[0],name);
  }
}

int test_in_list(List* l, char* name){
  if(l->first == NULL) return 0;
  Node *s = l->first;
  while(s){
    if (strcmp(s->name, name)== 0)
      return 1;
    s = s->next;
  }
  return 0;
}

int test_red_link(char* name, List Adj[], int n){
  for(int i = 1; i<n+1; i++){
    if (strcmp(Adj[i].name, name) == 0)
      return 0;
  }
  return 1;
}

int test(char* name, List *l, List Adj[], int n){
  if (test_in_list(l,name))
    return 0;
  if (test_red_link(name,Adj,n))
    return 0;

  return 1;
}

void feed_list(char* line, List* list, List Adj[], int n){
  while ((*line != '\n')&&(*line != '|'))
    line++;

  if (*line == '\n') return;

  while(*line != '\n'){
    line++;
    char* name = malloc(sizeof(char*));
    int i = 0;
    while ((*line != '|')&&(*line != '\n'))
      name[i++] = *(line++);

    if (test(name, list, Adj, n)){
      add_list(list,name);
      Adj[i].cpt_sort++;
    }
  }
}

void wiki(FILE* f, List Adj[], int n){
  rewind(f);
  for(int i = 1; i<n+1; i++){
    char* line = malloc(sizeof(char*));
    fgets(line,256,f);
    List* list = &Adj[i];
    feed_list(line, list, Adj, n);
  }
}


int main(int argc, char *argv[]){

  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
      printf("File not found\n");
      return 0;
  }


  int n = number_lines(file);
  List Adj[n+1];

  read_link(Adj, file);
  wiki(file,Adj,n);
  fclose(file);

  print_graph(Adj, n);

    return 0;
}
