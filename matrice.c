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


void graph_init_mat(FILE *f, List Adj[], int n){
    //printf("%d",n);
     Adj[0] = *(list_init("SuperNode"));                    
    Adj[0].cpt_sort = n; 
    for (int i=1; i<=n; i++){    
        char* value = malloc(sizeof(char*));
        sprintf(value,"%d",i);
       
        int cpt=0;
     for(int j=0; j<n; j++){
         int v=0;
         int w=0;
      //printf("j ===== %d\n", j);
           fscanf(f, "%d", &v);
           if(v==1){   
               cpt++;
            char* value1 = malloc(sizeof(char*));
            sprintf(value1,"%d",j);
           
            add_list(&Adj[i], value1);
            //free(value1);
    
        }
     }
    // printf("à la ligne %d il y a %d de 1\n",i,cpt);
     cpt++;
     Adj[i].cpt_sort = cpt;
     //printf("la nvl value est === %s\n  ", value);
      add_list(&Adj[i],value);                       
      add_list(&Adj[i],"SuperNode");                 
      add_list(&Adj[0],value);   
    }
    
     printf("\n");
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


float compare(Page Vec_Ex[], Page Vec_Res[], int n){
    float max = ((Vec_Ex[0].pageRank - Vec_Res[0].pageRank)/Vec_Res[0].pageRank)*100;
    for (int i = 1; i<n+1; i++){
        float val = ((Vec_Ex[i].pageRank - Vec_Res[i].pageRank)/Vec_Res[i].pageRank)*100;
        if (max<val)
            max = val;
    }
    return max;
}

void experience(char* filename, int k){
  FILE* f = fopen(filename,"r");
  if(f == NULL) {
    printf("File not found");
    return;
  }

  int n = size_matrix(f);
  fclose(f);

  List Adj[n+1];

  FILE* f1 = fopen(filename,"r");
  if(f1 == NULL) return;
  graph_init_mat(f1,Adj,n);
  //print_graph(Adj,n);

  List Adj_pred[n+1];
  pred(Adj, Adj_pred,n);
  Page* Vec_Res = recup_vec(f,n);
  fclose(f);

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
  printf("ecart max = %lf %%\n", ecart);
  return;
}
