int size_matrix(FILE* f);
void graph_init_mat(FILE* f, List Adj[], List Adj_pred[], int n);
Page* recup_vec(FILE* f, int n);
float compare(Page Vec_Ex[], Page Vec_Res[], int n);
void moy_max(Page Vec_Ex[], Page Vec_Res[], int n);
void experience(char* filename, int k);
