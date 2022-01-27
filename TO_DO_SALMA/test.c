#include<stdio.h>
#include<stdlib.h>
#define SIZE_BUFFER 256

int main(int argc, char *argv[]){
  char* name= malloc(SIZE_BUFFER);
  char* str = "Yousseffffff";
  for(int i = 0; str[i]!= '\0'; i++){
    name[i] = str[i];
  }
  printf("%s\n", name);
  free(name);
  char* str1 = "Salma";
  for(int i = 0; str1[i]!= '\0'; i++){
    name[i] = str1[i];
  }
  printf("%s\n", name);

    return 0;
}
