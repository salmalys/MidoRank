#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>                                                 
#include "list.h"
#include "calcul.h"
#include "matrice.h"
#include "wiki.h"


int main(int argc, char *argv[]){
  time_t begin = time(NULL);                                                                                                          //lancement du chronometre
  if (strcmp(argv[1],"-t") == 0){                                                                                                     //mode test: si le deuxième argument dans la ligne de commande est -t
    char* value = argv[2];                                                                                                            //récupère dans un char* value le deuxième argument
    int k = atoi(value);                                                                                                              //la fonction atoi() permet de convertir le char* value en entier dans k
    char* tab_files[6]= {"alea4-6.txt", "alea4-12.txt","alea10-40.txt","alea50-1000.txt","alea100-5000.txt","alea1000-10000.txt"};    //tableau contenant l'ensemble des fichiers test
    for (int i = 0; i<=5; i++){
      printf("Matrice du fichier %s\n", tab_files[i]);                                                          
      algorithm_mat(tab_files[i], k);                                                                                                 //applique l'agorithme de pagerank pour chaque matrice du tableau tab_files
    }
  }
  else if (strcmp(argv[1],"-n") == 0){                                                                                                //mode normal: si le deuxième argument dans la ligne de commande est -n
    FILE* file = fopen(argv[2], "r");                                                                                                 //ouverture du fichier a traiter 
    if (file == NULL) {                                                                                                               
        printf("Fichier non trouve\n");                                                                                               //affiche une erreur si le fichier n'est pas trouve
        return 0;                                                                                                                     //fin 
    }
    char* value = argv[3];                                                                                                            //sinon on recupere dans un char* value le caractere present dans le dernier argument de la ligne de commade
    int x = atoi(value);                                                                                                              //convertit le caractere dans value en entier et le stocke dans x
    int n = number_lines(file);                                                                                                       //recupere le nombre de pages du fichier                                                                                                    
    List Adj[n+1];                                                                                                                    //declaration du graphe Adj qui a n+1 liste (celle du SuperNoeud)
    algorithm_wiki(file,x, Adj, n);                                                                                                   //applique l'algorithme de pagerank au fichier 
  }
  else {
    printf("Veuillez consulter la notice READ ME.\n");                                                                                 //si les arguments ne spécifie pas le mode affichage d'une consigne
  }
  
 
  time_t end = time(NULL);                                                                                                              //fin du chronomètre
  printf("Le temps d'execution est de %.10f secondes\n", difftime(end, begin));                                                         //affiche le temps d'execution
  
  return 0;
}
