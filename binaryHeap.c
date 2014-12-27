/** A simple array based min heap */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 10

typedef struct heap_node {
    int key;
    void* value;
} heap_node;

typedef struct heap_t {
    heap_node** heap;
    heap_node* last;
    int capacity;
    int size;
} heap_t;

heap_t* init_heap(void)
{
    heap_t * new = malloc(sizeof(heap_t));
    new->heap = malloc(DEFAULT_SIZE*sizeof(heap_node));
    new->capacity = DEFAULT_SIZE;
    for(int i = 0 ; i < new->size; i++) {
        //new->heap[i] = malloc(sizeof(heap_node));
        new->heap[i] = NULL;
    }
    new->last = NULL;
    new->size = 0;
    return new;
}

heap_node* new_node(int key, void* value)
{
    heap_node *node = malloc(sizeof(heap_node));
    node->key = key;
    node->value = value;

    return node;
}

int get_parent(int index) { return (index - 1)/2;}
int left_index(int index) { return 2*index + 1;}
int right_index(int index){ return 2*index + 2;}

void swap_node(heap_t* heap, int index, int parent)
{
    heap_node *tmp = heap->heap[parent];
    heap->heap[parent] = heap->heap[index];
    heap->heap[index] = tmp;
}

void bubble_up(heap_t* heap, int index) {
    int parent;
    while(index > 0) {
        parent = get_parent(index);
        if(heap->heap[parent]->key < heap->heap[index]->key)
            break;
        swap_node(heap, index, parent);
        index = parent;
    }
}

void insert_new(heap_t* heap, int key, void* value)
{
    heap_node *new = new_node(key, value); 
    int index = heap->size;
    heap->heap[index] = new;
    bubble_up(heap, index);
    heap->size++;
}

void bubble_down(heap_t *heap) 
{
   int cur = 0;
   while (left_index(cur) < heap->size) {
       int left = left_index(cur);
       int right = right_index(cur);
       int small = left;
       if(right < heap->size) {
           if(heap->heap[left] > heap->heap[right])
               small = right;
       }
       if(heap->heap[small]->key >= heap->heap[cur]->key) 
           break;
       swap_node(heap, cur, small);
       cur = small;
   }
}

void remove_min(heap_t *heap)
{
    heap->heap[0] = heap->heap[heap->size-1];
    heap->heap[heap->size] = NULL;
    heap->size--;
    bubble_down(heap);
}

int main(void)
{
    char* v0 = "li";
    char* v1 = "hong";
    char* v2 = "zhe";
    heap_t *heap = init_heap();
    insert_new(heap, 9, (void*)v0);
    insert_new(heap, 5, (void*)v1);
    insert_new(heap, 6, (void*)v2);
    if((heap)->heap[0])
        printf("%d %s\n", (heap->heap)[0]->key, (char*)heap->heap[0]->value);
    remove_min(heap);
    if((heap)->heap[0])
        printf("%d %s\n", (heap->heap)[0]->key, (char*)heap->heap[0]->value);
    return 0;
}
