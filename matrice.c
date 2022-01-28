#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#define SIZE_BUFFER_line 100000                                                                 //Defini une constante pour la taille des lignes
#define SIZE_BUFFER_name 1000                                                                   //Defini une constante pour la taille des charactères

int size_matrix(FILE* f){
  int n = 0;
  char line[SIZE_BUFFER_line];
    while(fgets(line, sizeof(line), f)){
    if (strcmp(line,"\n")==0){                                                                //Permet de s'arreter à la premiere ligne qui est égal à un retour à la ligne, pour ne pas compter les lignes vace les Vecteurs résultat
            return n;
        }
    n++;                                                  
    }
    return n;
}


void graph_init_mat(FILE *f, List Adj[],List Adj_pred[], int n){                                //Remplit le graphe de Adj, sans la page du SuperNoeud, et le graphe de Adj_pred

    Adj_pred[0] = *(list_init("SuperNode"));                                                    //Initialise la liste de Adj_pred du SuperNoeud
    for (int w=1; w<=n+1; w++){                                                                                          
        char* value2 = malloc(sizeof(char*));                                                                                                 
        sprintf(value2,"%d",w);                                                                 //Permet de mettre l'entier w dans value2 en le transformant en chaine de characteère
        Adj_pred[w]=*(list_init(value2));                                                       //Initialise les noms de chaque liste de Adj_pred de la page 1 à celle n+1 
        add_list(&Adj_pred[w],value2);                                                          //Ajoute lui même à la liste de Adj_pred correspondantes, car chaque page est pointée par elle même
        add_list(&Adj_pred[w],"SuperNode");                                                     //Ajoute la page du SuperNoeud à la liste Adj_pred
    }
    for (int i=1; i<=n; i++){                                                                  //Parcourt les lignes
        char* value = malloc(sizeof(char*));                    
        sprintf(value,"%d",i);                                                                 //Met l'entier i dans une chaine de charactère value
        Adj[i]=*(list_init(value));                                                            //Initialise la liste Adj[i] au nom de value
        int cpt=0;                                                                             //Compteur pour compter le nombres de voisins sortants de la liste Adj[i]
     for(int j=0; j<n; j++){                                                                   //Parcourt sur les colonnes
         int v=0;
         fscanf(f, "%d", &v);                                                                  //Parcourt le fichier et recupère le premier entier qu'il trouve et le stock dans v
         if(v==1){                                                                             //Si l'entier récuperer est un 1 :
            cpt++;                                                                             //Incremente le compteur car il y a un voisin sortant en plus
            char* value1 = malloc(sizeof(char*));
            sprintf(value1,"%d",j+1);                                                          //Met l'entier j+1 dans le charactère value1, j+1 car on commence à la colonne 0 mais cette colonne on considère que son nom est 1
            add_list(&Adj[i], value1);                                                         //Ajoute à Adj[i] la valeur de value1
            add_list(&Adj_pred[j+1], value);                                                   //Ajoute au tableau des predecesseurs de la page du nom value 1, la page de nom value
    }
     }
      cpt++;                                                                                   //Incremente le compteur une fois car lui même appartient à sa liste
      Adj[i].cpt_sort = cpt;                                                                   
      add_list(&Adj[i],value);                                                                //S'ajoute lui 
      add_list(&Adj[i],"SuperNode");                                                          //Ajoute la page du SuperNoeud 
      add_list(&Adj_pred[0],value);                                                           //Ajoute chaque nom de liste au Adj_pred du SuperNoeud
    }
     Adj[0].name="SuperNode";                                                                 //Reinitialisation de Adj[0]
     Adj[0].first=NULL;                                                                       
     Adj[0].cpt_sort = n;

}


Page* recup_vec(FILE* f, int n){
  Page* Vec_Res = malloc(sizeof(Page)*(n+1));
  char line[256];
  fgets(line, sizeof(line), f);

  for(int i = 0; i<n+1; i++){
    if (i == 0) Vec_Res[i].name = "SuperNode";
    else{
      char* value = malloc(SIZE_BUFFER_name);
      sprintf(value,"%d",i);
      Vec_Res[i].name = value;
    }
    fscanf(f,"%Lf, ", &Vec_Res[i].pageRank);
  }
  return Vec_Res;
}


void moy_max(Page Vec_Ex[], Page Vec_Res[], int n){
    float ecart_max[n+1];
    float moy=0;
    ecart_max[0]=(fabs((Vec_Ex[0].pageRank - Vec_Res[0].pageRank)/Vec_Res[0].pageRank))*100;
    float max = ecart_max[0];
    for (int i = 1; i<n+1; i++){
        ecart_max[i] = (fabs((Vec_Ex[i].pageRank - Vec_Res[i].pageRank)/Vec_Res[i].pageRank))*100;
        moy+=ecart_max[i];
        if (max<ecart_max[i])
            max = ecart_max[i];
}
  moy=moy/(n+1);
  printf("ecart moy = %.10f %%\n", moy);
  printf("ecart max = %.10f %%\n\n", max);
}


void experience(char* filename, int k){
  FILE* f = fopen(filename,"r");
  if(f == NULL) {
    printf("File not found");
    return;
  }
  int n = size_matrix(f);
  List Adj[n+1];
  rewind(f);
  List Adj_pred[n+1];
  graph_init_mat(f,Adj,Adj_pred, n);
  //print_graph(Adj,n);
  //print_graph(Adj_pred,n);
  Page* Vec_Res = recup_vec(f,n);
  fclose(f);

  Page* Vec_Ex = start(Adj, n);
  float E;
  E = (float)1/(10*n);

  while (k--)
  update(Vec_Ex, Adj, Adj_pred, n, E);
  //print_graph(Adj,n);

  //printf("%s",Vec_Ex[1].name);
  //free_list(&Adj[0]);
  //list_free(Vec_Ex);
  //page_free(Vec_Ex);
  //printf("Vecteur experimental:\n");
  affiche_res(Vec_Ex,n);
  moy_max(Vec_Ex, Vec_Res, n);
  
  free_graph(Adj,n);
  free_vec(Vec_Ex, n);
  free_vec(Vec_Res, n);


  return;
}
