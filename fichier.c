#include<stdio.h>
#include<stdlib.h>

/*But:
Lire le fichier texte ligne par ligne
Pour chaque ligne, on déclare une liste chainée qui contiendra tous les sortants de la page de cette ligne.
Résultat attendu à l'affichage:
page : page4 ; page2 ;
page2: page5 ;
page3: page5 ; page6 ;
page4: page2 ;
page5: page4 ;
page6: page6 ;
*/

typedef struct{
	char* page;
	struct Node* next;
}Node;

typedef struct{
	char* name;
	Node* first;
}List;

Node* node_init(char* p);
void add_list(List* l, char* p);
List* list_init(char* line);
void read_line(char* filename);
void print_list(List* l);

Node* node_init(char* p){
	Node* s = malloc(sizeof(Node));
	if (s == NULL) return s;
	s->page = p;
	s->next = NULL;
	return s;
}

void add_list(List* l, char* p){
	if (l == NULL) return;
	Node* s = node_init(p);
	if (s == NULL) return;
	s->next = l->first;
	l->first = s;
} //ajout en début de liste d'une page


List* list_init(char* line){
  List *l= malloc(sizeof(List));
  if (l == NULL) return NULL;
  char* name = malloc(sizeof(char*));
  int i = 0;
  while (*(line)!= '|'){
    name[i++] = *(line++);
  }
  l->name = name;
	l->first = NULL;
  while(*(line)!= '\n'){
    char* page = malloc(sizeof(char*));
    int j = 0;
		line++;
    while (*(line)!= '\n'&&*(line)!= '|'){
      page[j++] = *(line);
			line++;
    }
		add_list(l,page);
  }
  return l;
}

void read_line(char* filename){
  FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("File not found\n");
		return;
	}
  char* line = malloc(sizeof(char*));

  while (fgets(line, sizeof(line), file)){
		//printf("%s",line);
		//List* l = list_init("page1|page2|page3\n"); //Cet appel fonctionne bien
    List* l = list_init(line);
  	//print_list(l);
  }
  fclose(file);
}

void print_list(List* l){
	if (l == NULL) return;
	Node* s = l->first;
	printf("%s: ", l->name);
	while(s!= NULL){
		printf("%s ; ",s->page);
		s = s->next;
	}
	printf("\n");
}

int main(int argc, char* argv[]){
  read_line(argv[1]);
  return 0;
}
