
#define ITER_AT_HEAD 0
#define ITER_AT_TAIL 1

typedef struct node {
    struct node* prev;
    struct node* next; 
    void* value;
} node;

typedef struct listIter {
    struct node* next;
    int direction;
} listIter;

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
void print_list(List* list);
node* search_node(List* list, void* value);
int contains(List* list, int(*cmp)(const void*, const void*), void* b);
listIter* create_iterator(List *list, int direction);
void list_rewind(List *list, listIter *iter);
void list_rewind_tail(List *list, listIter *iter);
node* iter_next(listIter *iter);

