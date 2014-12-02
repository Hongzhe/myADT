

typedef struct node {
    int value;
    struct node* next;
}node;


node* init(void);
void insert_at_head(node** head, int val);
void remove_node(node** head, int val);
node* search_node(node* head, int val);


