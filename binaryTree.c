#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dList.h"

typedef struct treeNode {
    int key;
    char* value;
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

typedef enum {
    GOOD = 0,
    WRONG = 2
} status;

treeNode* new_node(int key, char* value, treeNode* parent) 
{
    treeNode* new = malloc(sizeof(*new));
    new->key = key;
    new->value = value;
    new->parent = parent;
    new->left = NULL;
    new->right = NULL;

    return new;
}

status insert_node(treeNode *new, treeNode* p)
{
    treeNode* parent = p;
    if(parent == NULL)
        return WRONG;

    if(p->key > new->key) {
        if(parent->left == NULL)
            parent->left = new;
        else {
            parent = parent->left;
            insert_node(new, parent);
        }
    } else {
        if(parent->right == NULL)
            parent->right = new;
        else {
            parent = parent->right;
            insert_node(new, parent);
        }
    }

    return GOOD;
}

void search(int key, treeNode* start, char** result) {
    List* list = init_list();
    insert_at_head(list, start);
    while(list->size !=0) {
        treeNode *cur = (treeNode*)remove_at_head(list)->value;
        if(cur == NULL)
            continue;
        if(key == cur->key) {
            *result = cur->value;
            fprintf(stderr, "got it %s\n", *result);
            break;
        }
        else if(key > cur->key) {
            insert_at_head(list, cur->right);
        } else {
            insert_at_head(list, cur->left);
        }
    }
    free(list);
}


void print_tree(treeNode *start)
{
    List* list = init_list();
    insert_at_tail(list, (void*)start);
    
    while(list->size !=0) {
        node* n = remove_at_head(list);
        treeNode* node = (treeNode*)n->value;
        if(node == NULL) {
            fprintf(stderr, "%d ", 0);
            continue;
        }
        fprintf(stderr, "%d ", node->key);
        insert_at_tail(list, (void*)node->left);
        insert_at_tail(list, (void*)node->right);
    }

    free(list);
}


int main(int argc, char* argv[])
{
    
    treeNode *root = new_node(10,"li",NULL);
    treeNode *n1 = new_node(1,"hong", root);
    treeNode *n2 = new_node(12,"zhe", root);
    treeNode *n3 = new_node(2, "binary", root);
    treeNode *n4 = new_node(13, "tree", root);
    insert_node(n1, root);
    insert_node(n2, root);
    insert_node(n3, root);
    insert_node(n4, root);
    print_tree(root);
    char* result = malloc(sizeof(char) * 20);
    search(13, root, &result);
    fprintf(stderr, "key 13 - value: %s\n", result);
    
    free(result);
    return 0;
}
