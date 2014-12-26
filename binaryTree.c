#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binaryTree.h"
#include "dList.h"



treeNode* new_node(int key, void* value) 
{
    treeNode* new = malloc(sizeof(*new));
    new->key = key;
    new->value = value;
    new->left = NULL;
    new->right = NULL;

    return new;
}

void insert_new(treeNode **start, int key, void *value)
{
    treeNode *tmp;
    if(*start == NULL) {
        tmp = new_node(key, value);
        *start = tmp;
        return;
    } else if(left_or_right(*start, key)) {
        insert_new( &((*start)->left), key, value);
    } else {
        insert_new(&((*start)->right), key, value);
    }
}

int remove_tree_node(treeNode **tree, int key)
{
    treeNode *parent , *target, *cur;
    parent = target = NULL;
    binary_search(key, tree, &parent, &target); 
    if(target == NULL) {
        fprintf(stderr, "Not Founded\n");
        return -1;
    }

    /* node to be deleted has no child*/
    if(target->left == NULL && target->right == NULL) {
        if(parent->right == target)
            parent->right = NULL;
        else
            parent->left = NULL;

        free(target);
        return 0;
    }

    if(target->left != NULL && target->right == NULL) {
        if(parent->right == target)
            parent->right = target->left;
        else
            parent->left = target->left;
        free(target);
        return 0;
    } else if (target->left == NULL && target->right != NULL) {
         if(parent->right == target)
            parent->right = target->right;
        else
            parent->left = target->right;
        free(target);
        return 0;      
    }
    
    /* node to be deleted has two children */
    if(target->left != NULL && target->right != NULL) {
        cur = target->left;
        treeNode tmp = *target;
        while(cur->right != NULL) {
            cur = cur->right;
        }
        cur->right = tmp.right;
        if(target->left == cur)
            cur->left = NULL;
        else
            cur->left = tmp.left;
        *target = *cur; 
        cur = NULL;
    }
    return 0;
}

void binary_search(int key, treeNode **tree, treeNode **parent, treeNode **target)
{
    treeNode *cur = *tree;
    while(cur != NULL) {
        if(key == cur->key) {
            *target = cur;
            return;
        } 
        *parent = cur;
        if(left_or_right(cur, key)) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    *target = NULL;
}

void free_tree(treeNode** root)
{
    List *list = init_list();
    insert_at_tail(list, *root);
    while(list->size != 0) {
        treeNode *node =(treeNode*) (remove_at_head(list)->value);
        if(node == NULL) {
            continue;
        }
        insert_at_tail(list, node->left);
        insert_at_tail(list, node->right);
        free(node);
    } 
    free(list);
}

int left_or_right(treeNode *node, int key) {
    int result;
    result = node->key > key ? 1:0;
    return result;
}

void print_tree_level_order(treeNode *start)
{
    List* list = init_list();
    insert_at_tail(list, (void*)start);
    
    while(list->size !=0) {
        node* n = remove_at_head(list);
        treeNode* node = (treeNode*)n->value;
        if(node == NULL) {
            continue;
        }
        fprintf(stderr, "%d ", node->key);
        insert_at_tail(list, (void*)node->left);
        insert_at_tail(list, (void*)node->right);
    }
    free_list(list);
}

void print_tree_preorder(treeNode *tree)
{
    if(tree == NULL) {
        return;
    }
    printf("%d ", tree->key);
    print_tree_preorder(tree->left);
    print_tree_preorder(tree->right);
}

int main(int argc, char* argv[])
{
    treeNode *root = NULL;
    char* r_value = "li";
    char* value1 = " hong";
    char* value2 = "zhe";
    char* value3 = "binary";
    char* value4 = "search";
    char* value5 = "test";
    char* value6 = "tree";
    insert_new(&root, 9, (void*) r_value);
    insert_new(&root, 4, (void*) value1);
    insert_new(&root, 2, (void*) value2);
    insert_new(&root, 15, (void*) value3);
    insert_new(&root, 12, (void*) value4);
    insert_new(&root, 6, (void*) value5);
    insert_new(&root, 11,(void*) value6);
    
    print_tree_preorder(root);
    printf("\n");
    
    print_tree_level_order(root);
    printf("\n");
    
    
    treeNode *result, *parent;
    result = NULL;
    binary_search(4, &root, &parent, &result);
    if(result != NULL) 
        printf("key %d value: %s\n", result->key, (char*)result->value);
    
    int removeReturn = remove_tree_node(&root, 4);
    printf("after remove 4 %d\n", removeReturn);
    
    print_tree_level_order(root);
   
    remove_tree_node(&root, 2);
    print_tree_level_order(root); 
    free_tree(&root);
    
    return 0;
}
