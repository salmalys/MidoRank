#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>                                                 
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include "wiki.h"


int main(int argc, char *argv[]){
  time_t begin = time(NULL);                                                                                                          //lancement du chronomètre
  if (strcmp(argv[1],"-t") == 0){                                                                                                     //Si le deuxième argument dans la ligne de commande est t
    char* value = argv[2];                                                                                                            //On récupère dans un char * le deuxième argument
    int k = atoi(value);                                                                                                              //La fonction atoi() permet de transforme le char* value en entier dans k

    char* tab_files[6]= {"alea4-6.txt", "alea4-12.txt","alea10-40.txt","alea50-1000.txt","alea100-5000.txt","alea1000-10000.txt"};

    for (int i = 0; i<=5; i++){
      printf("Matrice du fichier %s\n", tab_files[i]);                                                          
      experience(tab_files[i], k);                                                                                                    //Effectué pour chaque case du tableau tab-files[]
    }
  }

  else if (strcmp(argv[1],"-n") == 0){                                                                                                //Si le deuxième argument dans la ligne de commande est -n
    FILE* file = fopen(argv[2], "r");                                                                                                 //On ouvre le fichier indiqué en troisième
    if (file == NULL) {                                                                                                               //Si il n'est pas présent
        printf("File not found\n");
        return 0;                                                                                                                     //fin
    }

    char* value = argv[3];                                                                                                            //Sinon on recupère dans un char* le charactère présent dans le 4ème argument de la ligne de commade
    int x = atoi(value);                                                                                                              //Transforme le charactère dans value en entier et le stocke dans x

    int n = number_lines(file);                                                                                                     
    List Adj[n+1];                                                                                                                    //Créer le graphe Adj qui a n+1 pageq

    algorithm(file,x, Adj, n);

  }
  else {
    printf("Veuillez consulter la notice READ ME\n");
  }
time_t end = time(NULL);                                                                                                              //fin du chronomètre
printf("le temps d'execution : %.10f secondes\n", difftime(end, begin));                                                              //Affiche le temps d'excecution
  return 0;
}
