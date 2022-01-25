#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"

int size_matrix(FILE* f){
  int n = 0;
  char line[256];                                                   //pas besoin de recuperer toute la ligne donc 256 suffit
    while(fgets(line, sizeof(line), f)){
    if (strcmp(line,"\n")==0){                                      //pour ne recuperer que les nombres de lignes de la matrice et sans les vecteurs 
            return n;
        }
    n++;
    }
    return n;
}

void graph_init_mat(FILE* f, List Adj[], int n){
    Adj[0] = *(list_init("SuperNode"));                     ///initialise ADJ[0} pour le SuperNoeud
    //Adj[0].name = "S";
    //Adj[0].first = NULL;
    Adj[0].cpt_sort = n;                                    //n=nombre de lignes


    for(int i = 1; i<n+1; i++){
      char* value = malloc(sizeof(char*));
      sprintf(value,"%d",i);                             //permet de transformer un entier en char*
      Adj[i] = *(list_init(value));                     //permet d'appeler la i eme page 'i'
      //Adj[i].name = value;
      //Adj[i].first = NULL;
      int cpt = 1;                                      //debute à 1 car il a forcement lui meme en voisin sortant

      char line[256];
      fgets(line, sizeof(line), f);
          int k = 0;
          while(line[k]!='\n'){
            for(int j = 1; j<n+1; j++){
              if (line[k] == '1'){
                char* value = malloc(sizeof(char*));
                sprintf(value,"%d",j);
                add_list(&Adj[i],value);
                cpt++;
              }
                k+=2;
              }
          }
      Adj[i].cpt_sort = cpt;
      add_list(&Adj[i],value);                        //permet de s'ajouter lui meme à sa liste
      add_list(&Adj[i],"SuperNode");                  //permet d'ajouter le supernoeud à la liste de nom Adj[i]
      add_list(&Adj[0],value);                        //permet d'ajouter la page au supernoeud
    }
}


Page* recup_vec(FILE* f, int n){                    //recuperer les vecteurs resultat écrit dans les fichiers
  Page* Vec_Res = malloc(sizeof(Page)*(n+1));
  char line[256];
  fgets(line, sizeof(line), f);

  for(int i = 0; i<n+1; i++){
    if (i == 0) Vec_Res[i].name = "SuperNode";    //le premier resultat est celui du supernoeud
    else{
      char* value = malloc(sizeof(char*));
      sprintf(value,"%d",i);
      Vec_Res[i].name = value;                //ajoute le resultat à la i eme place à la i eme page
    }
    fscanf(f,"%Lf, ", &Vec_Res[i].pageRank);
  }
  return Vec_Res;
}


float compare(Page Vec_Ex[], Page Vec_Res[], int n){                  //compare le resultat calculer grace à uptade à ceux mis dans le fichiers
    float max = ((Vec_Ex[0].pageRank - Vec_Res[0].pageRank)/Vec_Res[0].pageRank)*100;
    for (int i = 1; i<n+1; i++){
      //ajouter valeur absolue
        float val = ((Vec_Ex[i].pageRank - Vec_Res[i].pageRank)/Vec_Res[i].pageRank)*100;     // formule : (|valeur exp - valeur res| / valeur res) * 100
        if (max<val)
            max = val;
    }
    return max;                                           //retourne le plus grand pourcentage d'erreur
}

void experience(FILE *f, int k){

  int n = size_matrix(f);
  rewind(f);                                           //permet de reboucler au debut du fichier

  List Adj[n+1];

  graph_init_mat(f,Adj,n);
  //print_graph(Adj,n);

  List Adj_pred[n+1];
  pred(Adj, Adj_pred,n);
  Page* Vec_Res = recup_vec(f,n);
  
  Page* Vec_Ex = start(Adj, n);
  long double E;
  E = (long double)1/(10*n);

  while (k--)
    update(Vec_Ex, Adj, Adj_pred, n, E);

  //printf("Vecteur experimental:\n");
  //affiche_res(Vec_Ex,n);
  
  //printf("Vecteur resultat:\n");
  //affiche_res(Vec_Res,n);

  float ecart = compare(Vec_Ex, Vec_Res, n);
  printf("ecart max = %.20lf %%\n", ecart);     //.20 pour afficher 20 chiffres apres la virgule
  return;
}
