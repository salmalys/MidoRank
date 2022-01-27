#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"

int size_matrix(FILE* f){
  int n = 0;
  char line[256];
    while(fgets(line, sizeof(line), f)){
    if (strcmp(line,"\n")==0){
            return n;
        }
    n++;
    }
    return n;
}

/*void graph_init_mat(FILE* f, List Adj[], List Adj_pred[], int n){
    Adj[0] = *(list_init("SuperNode"));
    //Adj[0].name = "S";
    //Adj[0].first = NULL;
    Adj[0].cpt_sort = n;


    for(int i = 1; i<n+1; i++){
      char* value = malloc(sizeof(char*));
      sprintf(value,"%d",i);
      Adj[i] = *(list_init(value));
      //Adj[i].name = value;
      //Adj[i].first = NULL;
      int cpt = 1;

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
      add_list(&Adj[i],value);
      add_list(&Adj[i],"SuperNode");
      add_list(&Adj[0],value);
    }
}*/



void graph_init_mat(FILE *f, List Adj[],List Adj_pred[], int n){
    Adj[0] = *(list_init("SuperNode"));
    Adj[0].cpt_sort = n;
    Adj_pred[0] = *(list_init("SuperNode"));
    for (int w=1; w<=n+1; w++){
        char* value2 = malloc(sizeof(char*));
        sprintf(value2,"%d",w);
        Adj_pred[w]=*(list_init(value2)); //obliger de tout initaliser avant pour les pred
        add_list(&Adj_pred[w],value2);
        add_list(&Adj_pred[w],"SuperNode");
    }
    for (int i=1; i<=n; i++){
        char* value = malloc(sizeof(char*));
        sprintf(value,"%d",i);
       Adj[i]=*(list_init(value));
        int cpt=0;
     for(int j=0; j<n; j++){
         int v=0;

         fscanf(f, "%d", &v);
         if(v==1){
            cpt++;
            char* value1 = malloc(sizeof(char*));
            sprintf(value1,"%d",j+1);
            add_list(&Adj[i], value1);
            add_list(&Adj_pred[j+1], value);
    }
     }
      cpt++;
      Adj[i].cpt_sort = cpt;
      add_list(&Adj[i],value);
      add_list(&Adj[i],"SuperNode");
      add_list(&Adj[0],value);
      add_list(&Adj_pred[0],value);
    }
     Adj[0].name="SuperNode";
}


Page* recup_vec(FILE* f, int n){
  Page* Vec_Res = malloc(sizeof(Page)*(n+1));
  char line[256];
  fgets(line, sizeof(line), f);

  for(int i = 0; i<n+1; i++){
    if (i == 0) Vec_Res[i].name = "SuperNode";
    else{
      char* value = malloc(sizeof(char*));
      sprintf(value,"%d",i);
      Vec_Res[i].name = value;
    }
    fscanf(f,"%Lf, ", &Vec_Res[i].pageRank);
  }
  return Vec_Res;
}


float ecart_max(Page Vec_Ex[], Page Vec_Res[], int n){
    float max = ((Vec_Ex[0].pageRank - Vec_Res[0].pageRank)/Vec_Res[0].pageRank)*100;
    for (int i = 1; i<n+1; i++){
        float val = ((Vec_Ex[i].pageRank - Vec_Res[i].pageRank)/Vec_Res[i].pageRank)*100;
        if (max<val)
            max = val;
    }
    return max;
}

float ecart_moy(Page Vec_Ex[], Page Vec_Res[], int n){
    float sum = ((Vec_Ex[0].pageRank - Vec_Res[0].pageRank)/Vec_Res[0].pageRank)*100;
    for (int i = 1; i<n+1; i++){
        sum += ((Vec_Ex[i].pageRank - Vec_Res[i].pageRank)/Vec_Res[i].pageRank)*100;
    }
    float res = (float)sum/n;
    return res;
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


  //pred(Adj, Adj_pred,n);
  //print_graph(Adj_pred,n);

  Page* Vec_Res = recup_vec(f,n);
  fclose(f);

  Page* Vec_Ex = start(Adj, n);
  float E;
  E = (float)1/(10*n);

  while (k--)
    update(Vec_Ex, Adj, Adj_pred, n, E);

  printf("Vecteur experimental:\n");
  affiche_res(Vec_Ex,n);

  printf("Vecteur resultat:\n");
  affiche_res(Vec_Res,n);

  float max = ecart_max(Vec_Ex, Vec_Res, n);
  float moy = ecart_moy(Vec_Ex, Vec_Res, n);
  printf("Ecart maximum = %.10f %%\n", max);
  printf("Ecart moyen = %.10f%%\n\n", moy);
  int sum = somme(Vec_Ex, n);
  return;
}
