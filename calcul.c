#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"

Page* start(List Adj[], int n){                                                  //initialise le premier Vecteur resultat des pagesrank à :
    Page* Vec = malloc(sizeof(Page)*(n+1));                                      //n+1 car n ne compte pas le SuperNoeud
    Vec[0].name = "SuperNode";
    Vec[0].pageRank = 0;                                                        //0 pour le SuperNoeud
    for (int i = 1; i<n+1; i++ ){
        Vec[i].name = Adj[i].name;
        Vec[i].pageRank = (long double)1/n;                                     //et 1/N pour les autres, long double pour pouvoir voir la division entiere de 1/N
    }
    return Vec;
}

void affiche_res(Page Vec[], int n){
    for (int i = 0; i<n+1; i++)
        printf("%s: Page Rank = %Lf\n", Vec[i].name, Vec[i].pageRank);
    printf("\n");
}


List* find(char* string, List Adj[], int n){                                    //trouver si string est dans la liste Adj 
    for(int i = 0; i<n+1; i++){
        if (strcmp(Adj[i].name,string)==0)
            return &Adj[i];                                                     //si oui retourne l'adresse
    }
    return NULL;
}

void init_Adj_pred(List Adj[], List Adj_pred[], int n){
    for(int i = 0; i<n+1; i++){
        Adj_pred[i] = *list_init(Adj[i].name);                                  //initialise la list adj_pred avec les noms de la liste adj
    }
}


void pred(List Adj[], List Adj_pred[], int n){                                  ///creer la liste des predecesseur
    init_Adj_pred(Adj, Adj_pred, n);
    for(int i = 0; i<n+1; i++){
        List list_principal = Adj[i];
        Node* node = list_principal.first;
        while(node){
            List* l = find(node->name, Adj_pred, n);                             //?????
            add_list(l,list_principal.name);
            node = node->next;
        }
    }
}

long double proba_u_s(List* u, char* s, int n, long double E){                   //proba de u_s 
  if(strcmp(u->name,"SuperNode")==0)                                             //cas si le nom de la Liste est le supernoeud
    return (long double)1/n;
  else if(strcmp(s,"SuperNode")== 0)                                             //si le nom de la page dont on calcule la probabilité est le supernoeud
    return E;   
  else{                                                                          //si c'est une liste comme les autres
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

void copie(Page Vec_pred[],Page Vec[], int n){                                  //permet d'enregistrer le vecteur calculer à chaque k 
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
        Vec[i].pageRank = 0;                                                    //initialisation à 0 du pagerank
        List* l = find(Vec[i].name, Adj_pred, n);                               //????
        //if(l == NULL) printf("prblm");
        Node* u = NULL;
        if (l != NULL) {
          u = l->first;
        }
        else{
          printf("erreur");
        }
        while (u){
            List* list_u = find(u->name, Adj,n);
            long double p = proba_u(u->name,Vec_pred,n);
            Vec[i].pageRank += proba_u_s(list_u,Vec[i].name, n,E)*p;
            u = u->next;
        }
    }
}
