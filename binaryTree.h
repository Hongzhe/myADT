#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

typedef struct treeNode {
    int key;
    void* value;
    struct treeNode* parent;
    struct treeNode *left;
    struct treeNode *right;
} treeNode;

int left_or_right(treeNode *node, int key);
treeNode* new_node(int key, void* value);
void free_tree(treeNode **tree);
void insert_new(treeNode **tree, int key, void* value);
int  remove_tree_node(treeNode **tree, int key);
void binary_search(int key, treeNode **tree, treeNode **parent, treeNode **target);
void print_tree_preorder(treeNode *tree);
void print_tree_level_order(treeNode *tree);

#endif
