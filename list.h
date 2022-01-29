/*Contenu de la bibilotheque list
-structure d'une liste chainee pour la reprentation du graphe
-fonctions de bases associees aux listes
-fonctions d'affichage d'une liste et du graphe
-fonctions de liberation de la memoire allouee*/

struct node{
    char* name;
    struct node* next;
};
typedef struct node Node;

struct list{
    char* name;
    Node* first;
    int cpt_sort;
};
typedef struct list List;


List* list_init(char*);
Node* node_init(char*);
void add_list(List*, char*);
void print_list(List* l);
void print_graph(List*, int);
void free_list(List* l);
void free_graph(List Adj[], int n);
