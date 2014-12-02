
typedef struct node {
    struct node* prev;
    struct node* next; 
    void* value;
} node;

typedef struct List {
    node* head;
    node* tail;
    int size;
} List;


List* init_list(void);
void free_list(List* list);
void insert_at_head(List* list, void* val);
void insert_at_tail(List* list, void* val);
node* remove_node(List* list, int(*cmp)(const void*, const void*), void* b);
node* remove_at_head(List* list);
node* remove_at_tail(List* list);
int contains(List* list, int(*cmp)(const void*, const void*), void* b);
