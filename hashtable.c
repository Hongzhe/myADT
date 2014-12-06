#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

hashtable* create_new(void) {
    hashtable* table = malloc(sizeof(hashtable*));
    table->capacity = DEFAULT_SIZE;
    table->container = malloc(sizeof(entry*) * table->capacity);
    for(int i = 0; i < table->capacity; i++) {
        table->container[i] = malloc(sizeof(entry*));
        table->container[i]->pair = malloc(sizeof(pair*));
        table->container[i]->deleted = 0;
    
    }
    table->size = 0;

    return table;
}

pair* create_entry(char* key, void* value) {
    //entry* new = malloc(sizeof(entry*));
    pair* newpair = malloc(sizeof(pair*));
    newpair->key = key;
    newpair->value = value;

    return newpair;
}

void insert_entry(hashtable* table, char* key, void* value) {
    long hash = ELFHash(key);
    int index = hash % table->capacity;
    pair* new = create_entry(key, value);

    entry** container = table->container;
    if((container[index])->pair->key == NULL) { // new key
        (container[index])->pair = new;
    } else { // collision happened
        int prob = index + 1;
        int insert_ok = 0;
        for(;prob % table->capacity != index; prob ++) {
            if((*container + prob)->pair->key == NULL) {
                (*container + prob)->pair = new;
                insert_ok = 1;
                break;
            }
        } 
        if(insert_ok == 0) {
            fprintf(stderr, "need resize the table\n");
        }// need go back to handle the resize issue.
    }
    table->size ++;
}

int get_index(hashtable* table, char* key) {
    long hash = ELFHash(key);
    int index = hash % table->capacity;

    return index;
}

int is_match(hashtable* table, char* key, int index) {
    int matched = 0;
    if(table->container[index]->pair->key != NULL &&
            strcmp(table->container[index]->pair->key, key) == 0) {
        matched = 1;
    }

    return matched; 
}
void* look_up(hashtable* table, char* key) {
    long hash = ELFHash(key);
    int index = hash % table->capacity;
    void* result = NULL;
    entry** container = table->container;
    if(container[index]->pair->key != NULL &&
            strcmp(container[index]->pair->key, key) ==0 ) {
        result = container[index]->pair->value;
    } else {
        int capacity =  table->capacity;
        for(int prob = index + 1; prob % capacity != index; prob++) {
            if(container[prob]->pair->key != NULL && 
                    strcmp(container[prob]->pair->key, key) == 0) {
                result = container[prob]->pair->value;
            }
        }  
    }

    return result;
}

void delete_entry(hashtable* table, char* key) {
    int index = get_index(table, key);
    int matched = is_match(table, key, index);
    if(matched) {
        table->container[index]->pair->key = NULL;  //need to free do it later
        table->container[index]->deleted = 1;
        table->size --;   
    } else {
        for(int prob = index+1; prob % table->capacity != index; prob++) {
            matched = is_match(table, key, prob);
            if(matched) {
                table->container[prob]->pair->key = NULL;  //need to free do it later
                table->container[prob]->deleted = 1;
                table->size--;   
                break;
            } 
        }
    }
}


int main(int argc, char* argv[]) {
    hashtable* table = create_new();
    char* s = "hong";
    int age = 24;
    insert_entry(table, s, (void*) &age);

    return 0;
}
