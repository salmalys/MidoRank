#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"

Page* start(List Adj[], int n){                                                                      //initaliser le vecteur resultat, vecteur des pageRank
    Page* Vec = malloc(sizeof(Page)*(n+1));                                                          //n+1 : car il y a n+1 pages, n+1 pageRank
    Vec[0].name = "SuperNode";                                                                       //initalisation à 0 du pageRank du SuperNoeud
    Vec[0].pageRank = 0;
    for (int i = 1; i<n+1; i++ ){                                                                    //parcours de toutes les pages                                
        Vec[i].name = Adj[i].name;                                                                   //initialisation du nom, meme nom que pour le graphe
        Vec[i].pageRank = (long double)1/n;                                                          //initalisation du pageRank à  1/n
    }
    return Vec;
}

void affiche_res(Page Vec[], int n){
    for (int i = 0; i<n+1; i++)
        printf("%s: Page Rank = %.20Lf\n", Vec[i].name, Vec[i].pageRank);                            //.20 : permet d'afficher 20 chiffres après la virgule
    printf("\n");
}


List* find(char* string, List Adj[], int n){                                                         //renvoie la liste dont le nom est donne en parametre
    for(int i = 0; i<n+1; i++){                                                                      //parcours du graphe
        if (strcmp(Adj[i].name,string)==0)                                                           //comparaison du nom de la liste et de string
            return &Adj[i];                                                                          //Retourne l'adresse de la liste qui a pour nom le string
    }
    return NULL;                                                                                     
}

void init_Adj_pred(List Adj[], List Adj_pred[], int n){                                              //Initialise les noms de la liste des predecesseurs utilisees pour les listes wikipedia
    for(int i = 0; i<n+1; i++){                                                         
        Adj_pred[i] = *list_init(Adj[i].name);
    }
}


void pred(List Adj[], List Adj_pred[], int n){                                                     //remplit le graphe Adj_pred en focntion des donnees de Adj                                                   
    init_Adj_pred(Adj, Adj_pred, n);                                                               
    for(int i = 0; i<n+1; i++){
        List list_principal = Adj[i];                                                               //pour une liste fixee 
        Node* node = list_principal.first;
        while(node){                                                                                //parcours des noeuds de cette liste
            List* l = find(node->name, Adj_pred, n);                                                //ajout a la liste de node le nom de la liste fixee 
            add_list(l,list_principal.name);
            node = node->next;
        }
    }
}

long double proba_u_s(List* u, char* s, int n, long double E){                                      //calcul de la probabilite que le noeud u pointe vers le noeud s
  if(strcmp(u->name,"SuperNode")==0)                                                                //si le nom de la liste u est "SuperNode" 
    return (long double)1/n;                                                                        //on renvoit la probabilité 1/n
  else if(strcmp(s,"SuperNode")== 0)                                                                //si le nom de la page s est "Supernode"
    return E;                                                                                       //on renvoit epsilon = E
  else{
        return (long double)(1-E)/u->cpt_sort;                                                      //sinon on renvoie la formule (besoin de recuperer la liste u pour recuperer le nombre des sortants de u;
    }
}

long double proba_u(char* name, Page Vec[], int n){                                                 //calcul de la probabilité de la liste u
    for(int i = 0; i<n+1; i++){
        if (strcmp(Vec[i].name,name)==0){                                                           //permet de trouver quel Vecteur a pour nom le nom de u
            return Vec[i].pageRank;                                                                 //pageRank du Vecteur éxperimental qui a pour nom u
        }
    }
    return 0;                                                                                       //si il n'existe pas retourne 0
}

void copie(Page Vec_pred[],Page Vec[], int n){                                                      //copie du vecteur initial dans Vec_pred
    for (int i=0; i<n+1; i++){                                                                      
        Vec_pred[i].name=Vec[i].name;
        Vec_pred[i].pageRank=Vec[i].pageRank;
    }
}

void update(Page Vec[], List Adj[], List Adj_pred[], int n, long double E){                        //mise a jour du vecteur experimental
    Page Vec_pred[n+1];                                                                            //declaration du Vec_pred contenant les pageRank precedents
    copie(Vec_pred,Vec, n);                                                                        //copie du Vec dans Vec_pred, necessaire pour ne pas fausser les calculs
    for(int i = 0; i<n+1; i++){                                                                    //parcours du vecteur pour recalculer chaque pageRank
        Vec[i].pageRank = 0;                                                                       //pour une page fixee, initialise le pageRank à 0 
        List* l = find(Vec[i].name, Adj_pred, n);                                                  //cherche la liste contenant les predecesseurs de cette page
        Node* u = NULL;                                                                            
        if (l != NULL) {                                                                           //test si la liste n'est pas vide
          u = l->first;                                                                            //Si elle ne l'est pas, postion en debut de liste
        }
        else{
          printf("erreur");
        }
        while (u){                                                                                 //parcours de la liste des predecesseurs 
            List* list_u = find(u->name, Adj,n);                                                   //pour un predecesseur u fixe, recupere la liste associee a le page u 
            long double p1 = proba_u(u->name,Vec_pred,n);                                          // calcul de probabilité d'aller de u vers s 
            long double p2 = proba_u_s(list_u,Vec[i].name, n,E)                                    //calcul de la probabilité de u                            
            Vec[i].pageRank += p1*p2;                                                              //ajout du resulat au page Rank de la page 
            u = u->next;                                                                           //predecesseur suivant
        }
    }
}

void free_vec(Page* Vec, int n){                                                                   //libere l'espace memoire utilise par le Vecteur 
  for(int i = 0; i<n+1; i++){
    Vec[i].name = NULL;                                                                            //initialise chaque nom à NULL
  }
  free(Vec);                                                                                       //libere le Vec
}
