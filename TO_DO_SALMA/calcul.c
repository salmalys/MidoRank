#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"

Page* start(List Adj[], int n){
    Page* Vec = malloc(sizeof(Page)*(n+1));
    Vec[0].name = "SuperNode";
    Vec[0].pageRank = 0;
    for (int i = 1; i<n+1; i++ ){
        Vec[i].name = Adj[i].name;
        Vec[i].pageRank = (long double)1/n;
    }
    return Vec;
}

void affiche_res(Page Vec[], int n){
    for (int i = 0; i<n+1; i++)
        printf("%s: Page Rank = %Lf\n", Vec[i].name, Vec[i].pageRank);
    printf("\n");
}


List* find(char* string, List Adj[], int n){
    for(int i = 0; i<n+1; i++){
        if (strcmp(Adj[i].name,string)==0)
            return &Adj[i];
    }
    return NULL;
}

void init_Adj_pred(List Adj[], List Adj_pred[], int n){
    for(int i = 0; i<n+1; i++){
        Adj_pred[i] = *list_init(Adj[i].name);
    }
}


void pred(List Adj[], List Adj_pred[], int n){
    init_Adj_pred(Adj, Adj_pred, n);
    for(int i = 0; i<n+1; i++){
        List list_principal = Adj[i];
        Node* node = list_principal.first;
        while(node){
            List* l = find(node->name, Adj_pred, n);
            add_list(l,list_principal.name);
            node = node->next;
        }
    }
}

long double proba_u_s(List* u, char* s, int n, long double E){
  if(strcmp(u->name,"SuperNode")==0)
    return (long double)1/n;
  else if(strcmp(s,"SuperNode")== 0)
    return E;
  else{
        return (long double)(1-E)/u->cpt_sort;
    }
}

long double proba_u(char* name, Page Vec[], int n){
    for(int i = 0; i<n+1; i++){
        if (strcmp(Vec[i].name,name)==0){
            return Vec[i].pageRank;
        }
    }
    return 0;
}

void copie(Page Vec_pred[],Page Vec[], int n){
    for (int i=0; i<n+1; i++){
        Vec_pred[i].name=Vec[i].name;
        Vec_pred[i].pageRank=Vec[i].pageRank;
    }
}

void update(Page Vec[], List Adj[], List Adj_pred[], int n, long double E){
    Page Vec_pred[n+1];
    copie(Vec_pred,Vec, n);
    //Pour chaque page on recalcule son pageRank
    for(int i = 0; i<n+1; i++){
      //printf("\ni == %d\n", i);
        //initialisation à 0 du pagerank
        Vec[i].pageRank = 0;
        List* l = find(Vec[i].name, Adj_pred, n);
        //if(l == NULL) printf("prblm");
        Node* u = NULL;
        if (l != NULL) {
          u = l->first;
        }
        else{
          printf("erreur");
        }
        while (u){
            //printf("pred == %s\n", u->name);
            List* list_u = find(u->name, Adj,n);
            //print_list(list_u);
            long double p = proba_u(u->name,Vec_pred,n);
            //long double p2 = proba_u_s(list_u,Vec[i].name, n, E);
            //print_list(list_u);
            //printf("name == %s\n", Vec[i].name);
            //printf("nbresortants == %d\n", list_u->cpt_sort);
            //printf("p1 == %Lf\np2 == %Lf\n\n\n", p1, p2);
            Vec[i].pageRank += proba_u_s(list_u,Vec[i].name, n,E)*p;
            u = u->next;
        }

    }
}
