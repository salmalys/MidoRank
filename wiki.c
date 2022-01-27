#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include"wiki.h"
#define SIZE_BUFFER 100000

//prend le fihchier en arguments et renvoie son nombre de lignes
int number_lines(FILE* f){
  int n = 0;
  char line[SIZE_BUFFER];
  while (fgets(line, sizeof(line), f))
        n++;
  return n;
}



/*Initialisation du graphe
read_link remplit le graphe (vide) donné en argument
Pour chaque ligne on initialise une liste à laquelle on ajoute le lien du Super-Noeud et elle_même
+ initialisation de la liste du Super Noeud et ajout de chaque page*/

void read_link(List Adj[], FILE* f){
  rewind(f);                                       //déplace le curseur en début du fichier
  Adj[0] = *(list_init("SuperNode"));              //init de la liste du Super Noeud
  int j = 0;
  char line[SIZE_BUFFER];
  int i = 1;
  while (fgets(line, SIZE_BUFFER, f)){
    //printf("i == %i\n", i);
    i++;
    int k = 0;
    char*  name = malloc(256);
    //char name[SIZE_BUFFER];
    //char name[256];
    int i = 0;
    while((line[k]!= '|')&&(line[k]!= '\n'))
      name[i++] = line[k++];
    j++;
    //printf("%s", name);
                                      //Dans la variable name on récupère la première chaîne de la ligne
    Adj[j] = *(list_init(name));
    add_list(&Adj[j],name);
    add_list(&Adj[0],name);
    //free(name);
    //printf("compteur == %d\n", Adj[j].cpt_sort);  */                  //Ajout à la liste du Super Noeud, le lien de la page associée à la ligne
  }
  //printf("fin de 1");

}


/*Test d'appartenance à la liste
cherche un lien dans une liste à partir de ce nom
renvoie 1 si le lien est déjà dans la liste
renvoie 0 sinon
*/
int test_in_list(List* l, char* name){
  if(l->first == NULL) return 0;
  Node *s = l->first;
  while(s){                           //parcourt des noeuds de la liste
    if (strcmp(s->name, name)== 0)   //test si même nom
      return 1;
    s = s->next;
  }
  return 0;
}


/*Test lien rouge
cherche le nom du lien en tant que nom de liste dans le graphe
renvoie 1 si le lien est rouge
renvoie 0 sinon
*/
int test_red_link(char* name, List Adj[], int n){
  for(int i = 1; i<n+1; i++){                 //parcourt du graphe
    if (strcmp(Adj[i].name, name) == 0)       //test si même nom
      return 0;
  }
  return 1;                                   //le nom n'a pas été trouvé dans Adj
}



/*renvoie 1 si il faut ajouter le nom à la liste
renvoie 0 sinon*/
int test(char* name, List *l, List Adj[], int n){
  if (test_in_list(l,name))
    return 0;
  if (test_red_link(name,Adj,n))
    return 0;

  return 1;
}


/*Ajoute les sortants de la liste associée à la ligne*/
void feed_list(char* line, List* list, List Adj[], int n){
  while ((*line != '\n')&&(*line != '|'))
    line++;                                        //lecture de la ligne jusuq'au nom

  if (*line == '\n') {
    add_list(list,"SuperNode");
    return;
  }
  //printf("car == %c\n", *line);           //Si la page ne contient pas de lien, il n'ya rien à ajouter
  while(*line != '\n'){
    line++;
    char* name = malloc(256);
    //char name[SIZE_BUFFER];
    int i = 0;
    while ((*line != '|')&&(*line != '\n')){
      name[i++] = *(line++);
      //printf("car == %c\n", *line);
    }
    //printf("name == %s\n", name);
      //name[i++] = *(line++);
                                    //le nom de la page est récupéré dans la variable name
    if (test(name, list, Adj, n)){                //test si le nom est à ajouter dans la liste
      add_list(list,name);                        //ajoute à la liste le lien sortant si test positif
      list->cpt_sort++;                      //incrémentation du nombre de sortants
    }
    //free(name);
  }

  add_list(list,"SuperNode");
  //printf("Liste %s \ncompteur == %d\n\n",list->name, list->cpt_sort);
  //print_list(list);
}


/*Fonction clé:
lecture du fichier et ajouter des sortants à chaque liste de chauqe ligne*/

void wiki(FILE* f, List Adj[], int n){
  rewind(f);                                     //déplace le curseur en début du fichier
  for(int i = 1; i<n+1; i++){                   //parcourt du graphe
    char line[SIZE_BUFFER];
    fgets(line,sizeof(line),f);
                                        //récupération de la ligne
    List* list = &Adj[i];
    printf("ligne %d\n", i);
    feed_list(line, list, Adj, n);         //Ajout à la liste des sortants présents dans la ligne
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
  //print_graph(Adj, n);

  List Adj_pred[n+1];
  pred(Adj, Adj_pred,n);
  //print_graph(Adj_pred, n);

  Page* Vec = start(Adj, n);
  long double E;
  E = (long double)1/(10*n);

  int k = 1;
  while (k--)
    update(Vec, Adj, Adj_pred, n, E);

  affiche_podium(x, Vec, n);
  //affiche_res(Vec,n);
}
