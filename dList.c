#include <stdio.h>
#include <stdlib.h>

#include "dList.h"


List* init_list(void)
{
    List* list = malloc(sizeof(List*));
    list->size = 0;
    return list;   
}

void free_list(List* list) 
{
    node* curr = list->head;
    while(curr != NULL) {
        node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

void insert_at_head(List* list, void* val)
{
    node* new = malloc(sizeof(node*));
    new->value = val;

    if(list->head == NULL) {
        list->head = new;
        list->head->next = list->tail;
        list->tail = new;
        list->tail->prev = list->head;
    } else {
        list->head->prev = new;
        new->next = list->head;
        list->head = new;
    }
    list->size++;
}

void insert_at_tail(List* list, void* val)
{
    node* new = malloc(sizeof(node*));
    new->value = val;

    if(list->tail == NULL) {
        list->tail = new;
        list->tail->prev = list->head;
        list->head = new;
        list->head->next = list->tail;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }

    list->size++;
}

node* remove_node(List* list, int(*cmp)(const void*, const void*), void* b)
{
    node* current = list->head;
    //node* prev = NULL;
    while(current != NULL) {
        if(cmp(current->value, b)) {
            if(current->next == NULL) {
                current->prev->next = NULL;
                list->tail = current->prev;
            } else if(current->prev == NULL) {
                current->next->prev = NULL;
                list->head = current->next;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            list->size--;
            return current;
        }
        current = current->next;
    }
    return NULL;
}

node* remove_at_head(List* list) {

    node* tmp = list->head;
    if(list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
        list->size--;
        return tmp;
    }
    
    list->head = tmp->next;
    list->head->prev = NULL;
    list->size--;
    return tmp;
}

node* remove_at_tail(List* list) {
    node* tmp = list->tail;
    if(list->size == 1) {
        list->head = NULL;
        list->tail = NULL;
        list->size--;
        return tmp;
    }
    tmp->prev->next = NULL;
    list->tail = tmp->prev;
    list->size--;
    return tmp;
}
node* search_node(List* list, void* val)
{
    node* tmp = list->head;
    while(tmp != NULL) {
        if(*(int*)tmp->value == *(int*)val){
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}
/**
 * To find out if the list contains a specific node
*/
int contains(List* list, int(*cmp)(const void*, const void*), void* b) {
    int result = 0;
    for(node* current = list->head; current != NULL; current = current->next) {
        if(cmp(current->value, b)) {
            result = 1;
            return result;
        }
    }
    return result;
}

void print_list(List* list) {
    node* cur = list->head;
    while(cur != NULL) {
        printf(" %d ", *(int*)cur->value);
        cur = cur->next;
    }
    printf("\n");
}

/*
 * A sample compare function
*/
int compare(const void* a, const void*b)
{
    const int* ai = (int*)a;
    const int* bi = (int*)b;
    if (*ai == *bi)
        return 1;
    return 0;
}

/** Return a iterator 
 * if direct is 0, the iterator start from the head of list;
 * if direct is 1, the iterator start from the tail of list;
 */
listIter* create_iterator(List *list, int direct)
{
    listIter *iter = malloc(sizeof(iter));
    iter->direction = direct;
    if(direct) {
        iter->next = list->tail;
    } else {
        iter->next = list->head;
    }

    return iter;
}

void list_rewind(List *list, listIter *iter)
{
    iter->next = list->head;
    iter->direction = ITER_AT_HEAD;
}

void list_rewind_tail(List *list, listIter *iter)
{
    iter->next = list->tail;
    iter->direction = ITER_AT_TAIL;
}

/** Return the pointer to next node in the iterator or NULL is there is no node in the list.
 */ 
node* iter_next(listIter *iter)
{
    node *cur = iter->next;
    if(cur != NULL) {
        if(iter->direction) 
            iter->next = cur->prev;
        else
            iter->next = cur->next;
    }
    return cur;
}

