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
  while (fgets(line, sizeof(line), f))                            //Permet de s'arreter à la derniere nulle non nulle
        n++;
  return n;
}


void read_link(List Adj[], FILE* f){                             //Initialise le nom de chaque liste de Adj 
  rewind(f);                                                     //Reboucle au début du fichier
  Adj[0] = *(list_init("SuperNode"));    //Initialise la liste du SuperNoeud
  int j=0;
  char line[SIZE_BUFFER_line];
  while (fgets(line, SIZE_BUFFER_line, f)){                      //Récupère dans line les lignes une par une du fichier
    int k = 0;
    char*  name = malloc(SIZE_BUFFER_name);
    int i = 0;
    while((line[k]!= '|')&&(line[k]!= '\n'))
      name[i++] = line[k++];                                    //Recupère le nom de la liste, le premier mot avant le caractère '|'
    j++;
    Adj[j] = *(list_init(name));                               
    add_list(&Adj[j],name);                                     //Ajoute à elle même son nom
    add_list(&Adj[0],name);                                     //S'ajoute à la liste du Supernoeud
  }
}



int test_in_list(List* l, char* name){                         //Test la présence d'une chaine de caractère dans les noms des pages déjà ajoutés à la liste
  if(l->first == NULL) return 0;
  Node *s = l->first;
  while(s){
    if (strcmp(s->name, name)== 0)                             //Si elle existe déjà dans la liste retourne 1
      return 1;
    s = s->next;
  }
  return 0;                                                    //Si elle n'est pas présente retourne 0
}


int test_red_link(char* name, List Adj[], int n){
  for(int i = 1; i<n+1; i++){
    if (strcmp(Adj[i].name, name) == 0)                       //Test si la chaine de caractère est un des noms des listes du graphe de Adj_pred
      return 0;                                               //Si oui retourne O
  } 
  return 1;                                                   //Sinon retourne 1
}


int test(char* name, List *l, List Adj[], int n){       
  if (test_in_list(l,name))                                   //Permet d'éviter les redondances des pages
    return 0;
  if (test_red_link(name,Adj,n))                              //Permet de ne pas prendre en compte les liens rouges
    return 0;

  return 1;
}


void feed_list(char* line, List* list, List Adj[], int n){      //Remplit Adj liste par liste
  while ((*line != '\n')&&(*line != '|'))                       //Permet de ne pas prendre en compte la premiere chaine charactère de la ligne car c'est son nom qui a déjà été pris en compte
    line++;

  if (*line == '\n') {
    add_list(list,"SuperNode");
    return;
  }


  while(*line != '\n'){                                         //Parcourt toute la ligne
    line++;  
    char* name = malloc(SIZE_BUFFER_name);
    int i = 0;
    while ((*line != '|')&&(*line != '\n')){                    //Recupère le nom de chaque page séparées par le characère '|'
      name[i++] = *(line++);                          
    }

    if (test(name, list, Adj, n)){                              //Si le test a retourner 1 on peut donc ajouter la page à la liste 
      add_list(list,name);
      list->cpt_sort++;
    }
  }


  add_list(list,"SuperNode");                                   //Ajoute à chaque liste le SuperNoeud
}



void wiki(FILE* f, List Adj[], int n){
  rewind(f);                                                    //Reboucle au départ sur f
  for(int i = 1; i<n+1; i++){
    char line[SIZE_BUFFER_line];
    fgets(line,SIZE_BUFFER_line,f);                             

    List* list = &Adj[i];                             
    printf("ligne %d\n", i);
    feed_list(line, list, Adj, n);                              //Remplit Adj
  }
}

void affiche_podium(int x, Page* Vec, int n){                   //Affiche les x noms et PageRank des pages les plus importantes
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

  Page* Vec = start(Adj, n);
  long double E;
  E = (long double)1/(10*n);

  int k = 1;
  while (k--)
    update(Vec, Adj, Adj_pred, n, E);
  affiche_podium(x, Vec, n);
  
  free_graph(Adj,n);
  free_graph(Adj_pred, n);
  free_vec(Vec_res, n);
}
