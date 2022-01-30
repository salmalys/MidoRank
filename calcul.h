/*Contenu de la bibliotheque calcul
-structure Page, le resultat Vec est un tableau de Pages
-fonctions asssociees au vecteur print_vec, start et free_vec
-fonctions d'initialisation du graphe des predecesseurs Adj_pred (utilsees pour les fichiers wikpedia)
-fonctions annexes necessaires au calcul des probabilites
-fonction principale update qui effectue la mise a jour a partir des donnees 
                            et alimente le vecteur resultat*/

struct page{
    char* name;
    long double pageRank;
};
typedef struct page Page;

Page* start(List Adj[], int n);
void print_vec(Page Vec[], int n);
List* find(char* string, List Adj[], int n);
void init_Adj_pred(List Adj[], List Adj_pred[], int n);
void pred(List Adj[], List Adj_pred[], int n);
long double proba_u_s(List* u, char* s, int n, long double E);
long double proba_u(char* name, Page Vec[], int n);
void copy(Page Vec_pred[],Page Vec[], int n);
void update(Page Vec[], List Adj[], List Adj_pred[], int n, long double E);
void free_vec(Page* Vec, int n);
