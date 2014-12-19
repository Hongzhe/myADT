#include <stdio.h>
#include <stdlib.h>
#include "dList.h"

typedef struct treeNode {
    int value;
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

typedef enum {
    GOOD = 0,
    WRONG = 2
} status;

treeNode* new_node(int value, treeNode* parent) 
{
    treeNode* new = malloc(sizeof(*new));
    new->value = value;
    new->parent = parent;
    new->left = NULL;
    new->right = NULL;

    return new;
}

treeNode insert_node(treeNode *new, treeNode* p)
{
    treeNode* parent = p;
    if(parent == NULL)
        return WRONG;

    if(p->value > new->value) {
        if(parent->right == NULL)
            parent->right = new;
        else {
            parent = parent->right;
            insert_node(new, parent);
        }
    } else {
        if(parent->left == NULL)
            parent->left = new;
        else {
            parent = parent->left;
            insert_node(new, parent);
        }
    }

    return GOOD;
}
