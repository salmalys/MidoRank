#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"

Page* start(List Adj[], int n){                                                                      //Initaliser le Vecteur resultat Vec des probabilités
    Page* Vec = malloc(sizeof(Page)*(n+1));                                                          //n+1 : car il y a n+1 pages, n+1 probabilités
    Vec[0].name = "SuperNode";                                                                       //Initalisation à 0 du Vecteur Experimentaux du SuperNode
    Vec[0].pageRank = 0;
    for (int i = 1; i<n+1; i++ ){                                                                    //Initalisation des Vecteurs éxperimentaux de toutes les autres pages                                
        Vec[i].name = Adj[i].name;                                                                   //Initialisation du nom 
        Vec[i].pageRank = (long double)1/n;                                                          //Initalisation du pageRank à  1/n
    }
    return Vec;
}

void affiche_res(Page Vec[], int n){
    for (int i = 0; i<n+1; i++)
        printf("%s: Page Rank = %.20Lf\n", Vec[i].name, Vec[i].pageRank);                            //.20 : permet d'afficher 20 chiffres après la virgule
    printf("\n");
}


List* find(char* string, List Adj[], int n){                                                         //Chercher si une chaine de caractère est un d'un nom d'une liste de Adj
    for(int i = 0; i<n+1; i++){                                                                     
        if (strcmp(Adj[i].name,string)==0)                                                           //Compare les deux chaines de caractères
            return &Adj[i];                                                                          //Retourne l'adresse de la liste qui a pour nom le string
    }
    return NULL;                                                                                     //Si le string est un lien rouge on retourne NULL
}

void init_Adj_pred(List Adj[], List Adj_pred[], int n){                                              //Initialise les noms de la liste des prédécésseurs utilisées pour les listes wikipédia
    for(int i = 0; i<n+1; i++){
        Adj_pred[i] = *list_init(Adj[i].name);
    }
}


void pred(List Adj[], List Adj_pred[], int n){                                                     
    init_Adj_pred(Adj, Adj_pred, n);
    for(int i = 0; i<n+1; i++){
        List list_principal = Adj[i];
        Node* node = list_principal.first;
        while(node){                                                                                //Ajoute tous les noeuds qui pointent sur le nom de la liste
            List* l = find(node->name, Adj_pred, n);
            add_list(l,list_principal.name);
            node = node->next;
        }
    }
}

long double proba_u_s(List* u, char* s, int n, long double E){                                      //Calcul de la probabilité que la liste u pointe vers le noeud de la page s
  if(strcmp(u->name,"SuperNode")==0)                                                                //Si le nom de la liste u est "SuperNode" 
    return (long double)1/n;                                                                        //On renvoit la probabilité 1/n
  else if(strcmp(s,"SuperNode")== 0)                                                                //Si le nom de la page s est "Supernode"
    return E;                                                                                       //On renvoit epsilon = E
  else{
        return (long double)(1-E)/u->cpt_sort;                                                      //Sinon on renvoie la formule
    }
}

long double proba_u(char* name, Page Vec[], int n){                                                 //Calcul de la probabilité de la liste u
    for(int i = 0; i<n+1; i++){
        if (strcmp(Vec[i].name,name)==0){                                                           //Permet de trouver quel Vecteur a pour nom le nom de u
            return Vec[i].pageRank;                                                                 //PageRank du Vecteur éxperimental qui a pour nom u
        }
    }
    return 0;                                                                                       //Si il n'existe pas retourne 0
}

void copie(Page Vec_pred[],Page Vec[], int n){                                                      //Copie le Vecteur trouvé dans un autre Vecteur
    for (int i=0; i<n+1; i++){
        Vec_pred[i].name=Vec[i].name;
        Vec_pred[i].pageRank=Vec[i].pageRank;
    }
}

void update(Page Vec[], List Adj[], List Adj_pred[], int n, long double E){                        //Mis à jour du Vecteur éxperimental
    Page Vec_pred[n+1];                                                                            //Créer une page Vecteur_pred de n+1 case
    copie(Vec_pred,Vec, n);                                                                        //Copie du Vecteur calculé précédemment dans Vec_pred pour ne pas perdre les valeurs calculées precedemment
    for(int i = 0; i<n+1; i++){
        Vec[i].pageRank = 0;                                                                       //Initialise le Vecteur Vec à 0
        List* l = find(Vec[i].name, Adj_pred, n);                                                  //Chercher si le nom du Vecteur Vec est un des noms des listes de la page Adj, initialise la liste l à l'adresse de la page Adj
        Node* u = NULL;                                                                            
        if (l != NULL) {                                                                           //test si la liste n'est pas vide
          u = l->first;                                                                            //Si elle ne l'est pas, positionné le noeud u au premier noeud de la liste l
        }
        else{
          printf("erreur");
        }
        while (u){                                                                                 //Tant que le noeud n'est pas nul
            List* list_u = find(u->name, Adj,n);                                                   //On initialise l'adresse de la liste liste_u à l'adresse du Adj du nom du noeud de u
            long double p = proba_u(u->name,Vec_pred,n);                                           
            Vec[i].pageRank += proba_u_s(list_u,Vec[i].name, n,E)*p;                               //Somme les calculs des probabiilité de chaque noeud en utlisant les resultats dans le Vecteur précédent Vec_pred et modifie le Vecteur Vec
            u = u->next;
        }
    }
}

void free_vec(Page* Vec, int n){                                                                   //Permet de liberer l'espace utilisé des vecteurs Vec
  for(int i = 0; i<n+1; i++){
    Vec[i].name = NULL;                                                                            //Initialise chaque nom à NULL
  }
  free(Vec);                                                                                       //Libère le Vec
}
