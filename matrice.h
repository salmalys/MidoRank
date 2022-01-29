/*Contenu de la bibilotheque matrice
-fonctions de lecture du fichier et de recuperation des donnees (graphe et vecteur resultat)
-fonction de comparaison des vecteurs resultat et experimental
-fonction principale qui declare et initialise les objets Adj, Adj_pred, Vec_Ex et Vec_Res 
                         effectue la mise à jour k fois 
                         affiche les resultats*/

int size_matrix(FILE* f);
void graph_init_mat(FILE* f, List Adj[], List Adj_pred[], int n);
Page* recup_vec(FILE* f, int n);
void moy_max(Page Vec_Ex[], Page Vec_Res[], int n);
void algorithm_mat(char* filename, int k);
