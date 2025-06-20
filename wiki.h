/*Contenu de la bibilotheque wiki:
-fonctions de lecture du fichier number_lines, read_link et feed_list
-foncions de test pour les liens rouges et les doublons
-fonction d'affichage
-fonction principale qui initialise le graphe
                         effectue la mise a jour
                         affiche le podium*/

int number_lines(FILE* f);
void read_link(List Adj[], FILE* f);
int test_in_list(List* l, char* name);
int test_red_link(char* name, List Adj[], int n);
int test(char* name, List *l, List Adj[], int n);
void feed_list(char* line, List* list, List Adj[], int n);
void graph_init_wiki(FILE* f, List Adj[], int n);
void print_podium(int x, Page* Vec, int n);
void algorithm_wiki(FILE* file, int x);
