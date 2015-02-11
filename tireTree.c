#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tireTree.h"

tireNode* new_node(char c)
{
    tireNode *new = malloc(sizeof(tireNode*));
    new->count = 0;
    new->list = NULL;
    new->symbol = c; 
    return new;
}

tireNode** new_list(void)
{
    tireNode **list = malloc(sizeof(tireNode*) * POOL);
    for(int i = 0; i < POOL; i++) {
        list[i] = new_node('a' + i);
    }

    return list;
}

void free_tiretree(tireNode** list)
{
    for(int i = 0; i < POOL; i++) {
        free(list[i]);
    }
    free(list);
}

void insert_word(char* word, tireNode **root)
{
    size_t len = strlen(word);
    tireNode **tmp = root;
    for(int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        ++tmp[index]->count;
        if(tmp[index]->list == NULL) {
            tmp[index]->list = new_list();
        }
        tmp = tmp[index]->list;
    }
}

int get_frequency(char *prefix, tireNode **root)
{
    size_t len = strlen(prefix);
    int result = 0;
    tireNode **tmp = root;
    for(int i = 0; i < len; i++) {
        if(tmp == NULL || tmp[prefix[i] - 'a']->count == 0) {
            result = 0;
            break;
        }
        if(i == len - 1)
            result = tmp[prefix[i] - 'a']->count;

        tmp = tmp[prefix[i] - 'a']->list;
    }
    return result;
}
