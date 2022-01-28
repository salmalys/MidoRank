#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"


List* list_init(char* name){
    List *l = malloc(sizeof(List));
    if (l == NULL) return NULL;                                             //Test si la liste l n'est pas nulle : obligatoire pour pouvoir appliqué les lignes suivantes à la liste l
    l->name = name;
    l->first = NULL;
    l->cpt_sort = 1;
    return l;
}

Node* node_init(char* p){
    Node* s = malloc(sizeof(Node));
    if (s == NULL) return s;                                                //Test obligatoire
    s->name = p;
    s->next = NULL;
    return s;
}

void add_list(List* l, char* p){
    if (l == NULL) return;                                                  //Test obligatoire
    Node* s = node_init(p);
    if (s == NULL) return;                                                  //Vérifie si la fonction node_init a bien initialisé le noeud s
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
        n=n->next;                                                              //Permet de parcourir toutes les liste l
        s->name=NULL;                                                           //Met à nul le nom de chaque noeud
        free(s->name);                                                          //Libère l'espace pour le nom de chaque noeud
        free(s);                                                                //Libère le noeud
    }
    l=NULL;                                                                     //Met à nul la liste
    free(l);                                                                    //Libèere la liste
}


void free_graph(List Adj[], int n){                                             //Libère Adj
    for (int i=0; i<n+1; i++){
      free_list(&Adj[i]);                                                       //Libère chaque liste comprise dans Adj
    }
}
