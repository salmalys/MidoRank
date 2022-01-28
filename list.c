#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"


List* list_init(char* name){
    List *l = malloc(sizeof(List));
    if (l == NULL) return NULL;
    l->name = name;
    l->first = NULL;
    l->cpt_sort = 1;
    return l;
}

Node* node_init(char* p){
    Node* s = malloc(sizeof(Node));
    if (s == NULL) return s;
    s->name = p;
    s->next = NULL;
    return s;
}

void add_list(List* l, char* p){
    if (l == NULL) return;
    Node* s = node_init(p);
    if (s == NULL) return;
    s->next = l->first;
    l->first = s;
}

void print_list(List* l){
    if (l == NULL) return;
    Node* s = l->first;
    printf("%s: ", l->name);
    while(s!= NULL){
        printf("%s ; ",s->name);
        s = s->next;
    }
    printf("\n");
}

void print_graph(List Adj[], int n){
    for (int i = 0; i< n+1; i++){
        print_list(&Adj[i]);
    }
    printf("\n");
}

void free_list(List* l){
    if (l == NULL)  {
      free(l);
      return;
    }
    Node* n = l->first;
    Node* s;
    while(n!=NULL){
        s=n;
        n=n->next;
        s->name=NULL;
        free(s->name);
        free(s);
    }
    l=NULL;
    free(l);
}


void free_graph(List Adj[], int n){
    for (int i=0; i<n+1; i++){
      //printf("%s\n", Adj[i].name);
      free_list(&Adj[i]);
    }
}
