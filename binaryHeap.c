/** A simple array based min heap */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 3

#define LEFT_INDEX(a) 2*a+1
#define RIGHT_INDEX(a) 2*a+2
#define PARENT_INDEX(a) (a-1)/2

typedef struct heap_node {
    int key;
    void* value;
} heap_node;

typedef struct heap_t {
    heap_node** heap;
    int capacity;
    int size;
} heap_t;

heap_t* init_heap(void)
{
    heap_t * new = malloc(sizeof(heap_t));
    new->heap = malloc(DEFAULT_SIZE*sizeof(heap_node));
    new->capacity = DEFAULT_SIZE;
    for(int i = 0 ; i < new->size; i++) {
        (new->heap)[i] = NULL;
    }
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

void swap_node(heap_t* heap, int index, int target)
{
    heap_node *tmp = heap->heap[target];
    heap->heap[target] = heap->heap[index];
    heap->heap[index] = tmp;
}

void bubble_up(heap_t* heap, int index) {
    int parent;
    while(index > 0) {
        parent = PARENT_INDEX(index);
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

    if(heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->heap = realloc(heap->heap, heap->capacity);
        if(heap->heap == NULL) {
            fprintf(stderr, "realloc failed\n");
            exit(1);
        }
    }
}
void bubble_down(heap_t *heap) 
{
   int cur = 0;
   while (LEFT_INDEX(cur) < heap->size) {
       int left = LEFT_INDEX(cur);
       int right = RIGHT_INDEX(cur);
       int small = left;
       if(right < heap->size) {
           if(heap->heap[left]->key > heap->heap[right]->key)
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
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->heap[heap->size - 1] = NULL;
    heap->size --;
    bubble_down(heap);
}

int main(void)
{
    char* v0 = "li";
    char* v1 = "hong";
    char* v2 = "zhe";
    char* v3 = "heap";
    char* v4 = "binary";
    heap_t *heap = init_heap();
    insert_new(heap, 9, (void*)v0);
    insert_new(heap, 5, (void*)v1);
    insert_new(heap, 6, (void*)v2);
    insert_new(heap, 7, (void*)v3);
    insert_new(heap, 12,(void*)v4);
    
    if((heap)->heap[0])
        printf("%d %s\n", (heap->heap)[0]->key, (char*)heap->heap[0]->value);
    printf("5th is %d\n", heap->heap[4]->key);
    
    /*remove_min(heap);*/
    if((heap)->heap[2])
        printf("%d %s\n", (heap->heap)[2]->key, (char*)heap->heap[2]->value);
    return 0;
}
