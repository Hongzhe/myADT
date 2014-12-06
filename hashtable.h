
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

hashtable* create_new(void);
pair* create_entry(void);


void insert_entry(hashtable* table, char* key, void* value);
void look_up(hashtable* table, char* key);
void delete_entry(hashtable* table, char* key);


int get_index(hashtable* table, char* key);
int is_match(hashtable* table, char* key, int index);
