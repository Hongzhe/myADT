#ifndef TIRETREE_H
#define TIRETREE_H


#define POOL 26

typedef struct tireNode {
    int count;
    char symbol;
    struct tireNode** list;
} tireNode;

tireNode* new_node(char);
tireNode** new_list(void);
void insert_word(char*, tireNode**);
int get_frequency(char*, tireNode**);
void free_tiretree(tireNode**);

#endif
