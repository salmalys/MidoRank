#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "calcul.h"
#include "matrice.h"


int main(int argc, char *argv[]){

  if (strcmp(argv[1],"-t") == 0){
    char* value = argv[2];
    int k = atoi(value);

    char* tab_files[6]= {"alea4-6.txt", "alea4-12.txt","alea10-40.txt","alea50-1000.txt","alea100-5000.txt","alea1000-10000.txt"};

    for (int i = 0; i<5; i++){
      experience(tab_files[i], k);
    }
  }
  return 0;
}
