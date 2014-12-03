#include <stdlib.h>
#include "singleList.h"

node* init_list(void) {
    node* head = malloc(sizeof(node*));
    head->next = NULL;
    head->value = 0;

    return head;
}

void free_list(node* head) {
    while(head != NULL) {
        node* cur = head;
        free(head);
        head = cur;
    }
}
void insert_at_head(node** head, int val)
{
    node* new = malloc(sizeof(node*));
    new->value = val;

    new->next = *head;
    *head = new;
}

/**
 * Inspired by a article post on coolshell
 * http://coolshell.cn/articles/8990.html
 */
void remove_node(node** head, int val)
{
    for(node **curr = head; curr;) {
        node* entry = *curr;
        if(entry->value == val) {
            *curr = entry->next;
            free(entry);
        } else {
            curr = &entry->next;
        }
    }
}

node* search_node(node* head, int val)
{
    node* tmp = head;
    while(tmp->next) {
        if(tmp->value == val) {
            return tmp;
        }

        tmp = tmp->next;
    }
    return NULL;
}




