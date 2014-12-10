/**
 * This is a navi implementation of hashtable. This hashtable use linear probing to 
 * handle collosion. The hash function used is listed in hashFunctions.h.
 * This kind of hashtable doesn't consider the rehash issue. This feautre will be addded later.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashFunctions.h"

#define DEFAULT_SIZE 100

typedef struct pair {
    char* key;
    void* value;
} pair;

typedef struct entry {
    pair* pair;
    int deleted;
} entry;

typedef struct hashtable {
    entry** container;
    int size;
    int capacity;
} hashtable;


hashtable* init_hashtable(int capacity) {
    hashtable* table = malloc(sizeof(hashtable*));
    table->container = malloc(sizeof(entry*)*DEFAULT_SIZE);
    for(int i = 0 ; i < DEFAULT_SIZE; i++) {
        table->container[i] = malloc(sizeof(entry*));
        table->container[i]->pair = malloc(sizeof(pair*));
        table->container[i]->deleted = 0;
    }
    table->size = 0;
    table->capacity = DEFAULT_SIZE;
    
    return table;
}

void free_table(hashtable* table) {
    int capacity = table->capacity;
    for(int i = 0; i < capacity; i++) {
        free(table->container[i]);
    }
    free(table->container);
}


int get_index(char*key, int capacity) {
    long hash = ELFHash(key);
    int index = hash % capacity;

    return index; 
}

int matched(hashtable* table, char* key, int index) {
    entry** entries = table->container;
    int matched = 0;
    if( entries[index]->pair->key != NULL && strcmp(entries[index]->pair->key, key) == 0) {
        matched = 1;
    }
    return matched;
}


void set_deleted_flag(hashtable* table, int index) {
    table->container[index]->deleted &= 0;
}

void insert_entry(hashtable* table, char* key, void* value) {
    int index = get_index(key, table->capacity);
    entry** entries = table->container;
    pair* new = malloc(sizeof(pair*));
    new->key = key;
    new->value = value;
    if(entries[index]->pair->key == NULL || entries[index]->deleted == 1) {
        entries[index]->pair = new;
        reset_deleted_flag(table, index);
    } else {
        int capacity = table->capacity;
        int prob;
        if(index == capacity -1)
            prob = 0;
        else 
            prob = index + 1;
        while(prob > -1 && prob != index) {
            if(entries[prob]->pair->key == NULL || entries[prob]->deleted == 1) {
                entries[prob]->pair = new;
                reset_deleted_flag(table, prob);
                prob = -1;
            } else {
                if(prob == capacity)
                    prob = 0;
                else 
                    prob++;
            }
        }
    }
    table->size++;
}

void* look_up(hashtable* table, char* key) {
    int index = get_index(key, table->capacity);
    entry** entries = table->container;
    if(entries[index]->pair->key != NULL && strcmp(entries[index]->pair->key, key) == 0) {
        return entries[index]->pair->value;
    } else {
        int prob;
        int capacity = table->capacity;
        if(index == capacity)
            prob = 0;
        else 
            prob = index + 1;
        while(prob != -1 && prob != index) {
            if(entries[prob]->pair->key == NULL && entries[prob]->deleted = 1) {
                return NULL;
            }
            if(matched(table, key, prob)) {
                return entries[prob]->pair->value;
            } else {
               if(prob == (capacity -1))
                   prob = 0;
               else
                   prob++;
            }
        }
    }
    return NULL;
}


/** Delete a entry. If the entry is exist,return 0. otherwise, return -1
 */
int delete_entry(hashtable* table, char* key)
{
    int status = -1;
    int index = get_index(key, table->capacity);
    entry** entries = table->container;
    if(entries[index]->pair->key != NULL &&
            strcmp(entries[index]->pair->key, key) == 0) {
        entries[index]->pair->key = NULL;
        entries[index]->deleted = 1;
        status = 0;
    } else {
        int prob;
        int capacity = table->capacity;
        if(index == capacity - 1)
            prob = 0;
        else 
            prob = index + 1;
        while(prob != -1 && prob != index) {
            if(entries[prob]->pair->key == NULL) {
                status = -1;
                break;
            }
            if(entries[prob]->pair->key != NULL &&
                    strcmp(entries[prob]->pair->key, key) == 0) {
                entries[index]->pair->key = NULL;
                entries[index]->deleted = 1;
                status = 0;
                break;
            }
            if(prob == capacity)
                prob = 0;
            else
                prob++;
        }
    }

    return status;
}

int main(int argc, char* argv[]) {
    hashtable* table = init_hashtable(10);
    char* key1 = "li";
    int age1 = 24;
    char* key2 = "pp";
    int age2 = 25;
    insert_entry(table, key1, (void*)&age1);
    insert_entry(table, key2, (void*)&age2);

    int res1 = *(int*) look_up(table, key1);
    int res2 = *(int*) look_up(table, key2);
    
    delete_entry(table, key1);
    
    printf("res1 is %d \n res2 is %d\n", res1, res2);
    return 0;
}
