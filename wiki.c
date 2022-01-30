#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include"wiki.h"
#define SIZE_BUFFER_line 100000                                 //constante pour la lecture des lignes  
#define SIZE_BUFFER_name 1000                                   //constante pour la lecture des noms des pages 

int number_lines(FILE* f){
  int n = 0;
  char line[SIZE_BUFFER_line];
  while (fgets(line, sizeof(line), f))                           //s'arrete à la derniere ligne non nulle
        n++;
  return n;
}


void read_link(List Adj[], FILE* f){                             //initialise le nom de chaque liste de Adj 
  rewind(f);                                                     //revient au debut du fichier
  Adj[0] = *(list_init("SuperNode"));                            //initialise la liste du SuperNoeud
  int j=0;
  char line[SIZE_BUFFER_line];
  while (fgets(line, SIZE_BUFFER_line, f)){                      //recupere dans line les lignes une par une du fichier
    int k = 0;
    char*  name = malloc(SIZE_BUFFER_name);
    int i = 0;
    while((line[k]!= '|')&&(line[k]!= '\n'))
      name[i++] = line[k++];                                    //recupere le nom de la liste, le premier mot avant le caractere '|'
    j++;
    Adj[j] = *(list_init(name));                               
    add_list(&Adj[j],name);                                     //ajoute à la liste, le lien sur elle-même
    add_list(&Adj[0],name);                                     //ajoute à la liste du SuperNoeud, cette page
  }
}



int test_in_list(List* l, char* name){                          //test la presence d'une chaine de caractere dans les noms des pages déjà ajoutes a la liste
  if(l->first == NULL) return 0;
  Node *s = l->first;
  while(s){
    if (strcmp(s->name, name)== 0)                              //si la page est deja dans la liste retourne 1
      return 1;
    s = s->next;
  }
  return 0;                                                     //si elle n'est pas presente retourne 0
}


int test_red_link(char* name, List Adj[], int n){               //test si le nom donne en argument est celui d'une lien rouge
  for(int i = 1; i<n+1; i++){
    if (strcmp(Adj[i].name, name) == 0)                         //test si la chaine de caractère est un des noms des listes du graphe de Adj
      return 0;                                                 //si oui retourne O , ce n'est pas un lien rouge
  } 
  return 1;                                                     //sinon retourne 1
}


int test(char* name, List *l, List Adj[], int n){               //effectue les deux tests precedents 
  if (test_in_list(l,name))                                   
    return 0;
  if (test_red_link(name,Adj,n))                                //renvoie 0 si l'un des tests est vrai 
    return 0;

  return 1;                                                     //renvoie 1 sinon 
}


void feed_list(char* line, List* list, List Adj[], int n){      //remplit la liste en lisant les pages de line
  while ((*line != '\n')&&(*line != '|'))                       //avance jusqu'au premier mot, qui est le nom de la listee (deja traite)
    line++;

  if (*line == '\n') {                                         //si le caractère est '\n', la ligne ne contient pas de pages 
    add_list(list,"SuperNode");                                //ajout du SuperNoeud seulement  
    return;
  }
                                                                //sinon il faut traiter le reste de la ligne

  while(*line != '\n'){                                         //parcours toute la ligne jusqu'au '\n'
    line++;  
    char* name = malloc(SIZE_BUFFER_name);                      
    int i = 0;
    while ((*line != '|')&&(*line != '\n')){                    //recupere dans la variable name, le nom de la page jusqu'au caractere '|'
      name[i++] = *(line++);                          
    }

    if (test(name, list, Adj, n)){                              //si le test retourne 1, le lien n'est ni un lien rouge, ni un doublons
      add_list(list,name);                                      //on ajoute la page a la liste
      list->cpt_sort++;                                         //incrémente le compteur des sortants de la liste
    }
  }
  add_list(list,"SuperNode");                                   //ajoute a chaque liste le SuperNoeud
}



void graph_init_wiki(FILE* f, List Adj[], int n){               //remplit chaque liste du graphe a partir du contenu du fichier wiki
  rewind(f);                                                    //revient au debut du fichier
  for(int i = 1; i<n+1; i++){                                   //parcours des listes du graphe
    char line[SIZE_BUFFER_line];                             
    fgets(line,SIZE_BUFFER_line,f);                             //recuperation de la ligne                                                                            
    printf("ligne %d\n", i);                                    //affichage optionnel mais pratique pour observer l'avancee du programme lors des tests 
    feed_list(line, &Adj[i], Adj, n);                           //la liste du graphe est initialisee a partir de ligne 
  }
}

void affiche_podium(int x, Page* Vec, int n){                   //Affiche les x noms et PageRank des pages les plus importantes
  for(int j = 0; j<x; j++){                                     //boucle x fois pour recuperer le max
    int max = 0;
    for(int i = 1; i<n+1; i++){
      if (Vec[i].pageRank > Vec[max].pageRank)
        max = i;                                                //max recupere la Page de Vec ayant le pageRank le plus eleve
    }                                                           //affichage de cette Page
    printf("%d : %s\nPageRank = %.20Lf\n\n", j+1, Vec[max].name, Vec[max].pageRank);
    Vec[max].pageRank = -1;
  }
}

void algorithm_wiki(FILE* file, int x, List Adj[], int n){
  read_link(Adj, file);                                        //lecture du fichier en initialisant seulement les noms de chaque liste + quelques reglage
  graph_init_wiki(file,Adj,n);                                 //remplit le graphe en ajoutant a chaque liste ces liens
  fclose(file);                                                //fermeture du fichier

  List Adj_pred[n+1];                                         
  pred(Adj, Adj_pred,n);                                       //remplit le graphe des predecesseurs a partir de Adj

  Page* Vec = start(Adj, n);                                   //initialisation du vecteur resultat 
  long double E;
  E = (long double)1/(10*n);                                   //parametre E fixe

  int k = 1;                                                   //parametre k fixe
  while (k--)
    update(Vec, Adj, Adj_pred, n, E);                          //mise a jour effectuee k fois 
  
  affiche_podium(x, Vec, n);                                   //affichage des x premieres pages
  
  free_graph(Adj,n);                                           //liberation e la memoire allouee pour Adj, Adj_pred et Vec
  free_graph(Adj_pred, n);                      
  free_vec(Vec, n);
}
