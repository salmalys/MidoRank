#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include"wiki.h"
#define SIZE_BUFFER_line 100000
#define SIZE_BUFFER_name 1000

int number_lines(FILE* f){
  int n = 0;
  char line[SIZE_BUFFER_line];
  while (fgets(line, sizeof(line), f))
        n++;
  return n;
}


void read_link(List Adj[], FILE* f){
  rewind(f);
  Adj[0] = *(list_init("SuperNode"));
  int j = 0;
  char line[SIZE_BUFFER_line];
  int i = 1;
  while (fgets(line, SIZE_BUFFER_line, f)){
    i++;
    int k = 0;
    char*  name = malloc(SIZE_BUFFER_name);
    int i = 0;
    while((line[k]!= '|')&&(line[k]!= '\n'))
      name[i++] = line[k++];
    j++;
    Adj[j] = *(list_init(name));
    add_list(&Adj[j],name);
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

  if (*line == '\n') {
    add_list(list,"SuperNode");
    return;
  }


  while(*line != '\n'){
    //printf("hello\n");
    line++;
    char* name = malloc(SIZE_BUFFER_name);
    int i = 0;
    while ((*line != '|')&&(*line != '\n')){
      name[i++] = *(line++);
    }

    if (test(name, list, Adj, n)){
      add_list(list,name);
      list->cpt_sort++;
    }
  }


  add_list(list,"SuperNode");
}



void wiki(FILE* f, List Adj[], int n){
  rewind(f);
  for(int i = 1; i<n+1; i++){
    char line[SIZE_BUFFER_line];
    fgets(line,SIZE_BUFFER_line,f);

    List* list = &Adj[i];
    printf("ligne %d\n", i);
    feed_list(line, list, Adj, n);
  }
}

void affiche_podium(int x, Page* Vec, int n){
  for(int j = 0; j<x; j++){
    int max = 0;
    for(int i = 1; i<n+1; i++){
      if (Vec[i].pageRank > Vec[max].pageRank)
        max = i;
    }
    printf("%d : %s\nPageRank = %.20Lf\n\n", j+1, Vec[max].name, Vec[max].pageRank);
    Vec[max].pageRank = -1;
  }
}

void algorithm(FILE* file, int x, List Adj[], int n){
  read_link(Adj, file);
  wiki(file,Adj,n);
  fclose(file);

  List Adj_pred[n+1];
  pred(Adj, Adj_pred,n);

  //print_graph(Adj, n);

  Page* Vec = start(Adj, n);
  long double E;
  E = (long double)1/(10*n);

  int k = 1;
  while (k--)
    update(Vec, Adj, Adj_pred, n, E);
  free_graph(Adj,n);
  affiche_podium(x, Vec, n);
  //somme(Vec,n);
}
