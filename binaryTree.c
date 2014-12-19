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

treeNode* search_left_greatest(treeNode* start);
int is_leaf(treeNode *node);
int left_or_right(treeNode *node);
void replace_deleted_node(treeNode *target, treeNode *origin);

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

/** 
 * Remove a node from binary search Tree. Three situation
 * 1. the node is a leaf node.
 * 2. the node has either left or right child.
 * 3. the node has both left and right chiildren.
 */
void delete_node(treeNode *target) {
    treeNode *parent = target->parent;
    if(target->left == NULL && target->right==NULL) 
        if(parent->value > target->value)
            parent->left = NULL;
        else
            parent->right = NULL;
    else if(target->left == NULL) { 
        if(parent->key > target->key)
            parent->left = target->right;
        else
            parent->right = target->right;
    } else if(target->right == NULL){        //right child is null
        if(parent->key < target->key)
            parent->right = target->left;
        else
            parent->left = target->left; 
    } else {                                //target node has two children.
        treeNode* replacement = search_left_greatest(target);
        replace_deleted_node(replacement, target);
    }
    free(target);
}

void replace_deleted_node(treeNode* replacement, treeNode *origin) {
     if(left_or_right(origin)) {
        origin->parent->left = replacement;
    }
    else { 
       origin-> parent->right = replacement;
    }
    replacement->left = origin->left;
    origin->left->parent = replacement;
    replacement->right = origin->right;
    origin->right->parent= replacement;
}

treeNode* search_left_greatest(treeNode* start) {
    List* list = init_list();
    treeNode *result;
    insert_at_head(list, start->left);
    while(list->size != 0) {
        treeNode* node = (treeNode*) remove_at_tail(list)->value;
        if(is_leaf(node)) {
            result = node;
            break;
        }
        insert_at_head(list, (void*)node->right);
    }
    free(list);
    return result;
}

int left_or_right(treeNode* node) {
    int result;
    result = node->parent->key > node->key ? 1:0;
    return result;
}

int is_leaf(treeNode *node) {
    if(node->left ==NULL && node->right == NULL) 
        return 1;
    return 0;
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
