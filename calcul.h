struct page{
    char* name;
    long double pageRank;
};
typedef struct page Page;

Page* start(List Adj[], int n);
void affiche_res(Page Vec[], int n);
List* find(char* string, List Adj[], int n);
void init_Adj_pred(List Adj[], List Adj_pred[], int n);
void pred(List Adj[], List Adj_pred[], int n);
long double proba_u_s(List* u, char* s, int n, long double E);
long double proba_u(char* name, Page Vec[], int n);
void copie(Page Vec_pred[],Page Vec[], int n);
void update(Page Vec[], List Adj[], List Adj_pred[], int n, long double E);
int somme(Page Vec_Ex[], int n);
