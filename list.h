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


void test(void);
List* list_init(char*);
Node* node_init(char*);
void add_list(List*, char*);
void print_list(List* l);
void print_graph(List*, int);
