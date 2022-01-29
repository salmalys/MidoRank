#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"


List* list_init(char* name){
    List *l = malloc(sizeof(List));
    if (l == NULL) return NULL;                                             //test si la liste l n'est pas nulle : obligatoire pour pouvoir applique les lignes suivantes a la liste l
    l->name = name;
    l->first = NULL;
    l->cpt_sort = 1;
    return l;
}

Node* node_init(char* p){
    Node* s = malloc(sizeof(Node));
    if (s == NULL) return s;                                                //test obligatoire
    s->name = p;
    s->next = NULL;
    return s;
}

void add_list(List* l, char* p){
    if (l == NULL) return;                                                  //test obligatoire
    Node* s = node_init(p);
    if (s == NULL) return;                                                  //verifie si la fonction node_init a bien initialise le noeud s
    s->next = l->first;
    l->first = s;
}

void print_list(List* l){                                                  //affichage d'une liste, son nom suivis des noms de tous ces noeuds
    if (l == NULL) return;
    Node* s = l->first;
    printf("%s: ", l->name);
    while(s!= NULL){
        printf("%s ; ",s->name);
        s = s->next;
    }
    printf("\n");
}

void print_graph(List Adj[], int n){                                          //affichage de chaque liste du graphe. Une liste par ligne
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
        n=n->next;                                                              //parcourir des liste l
        s->name=NULL;                                                           //met a nul le nom de chaque noeud
        free(s->name);                                                          //libere l'espace pour le nom de chaque noeud
        free(s);                                                                //Libere le noeud
    }
    l=NULL;                                                                     //met à nul la liste
    free(l);                                                                    //libere la liste
}


void free_graph(List Adj[], int n){                                             //libere le graphe Adj
    for (int i=0; i<n+1; i++){
      free_list(&Adj[i]);                                                       //Libere chaque liste du graphe Adj
    }
}
