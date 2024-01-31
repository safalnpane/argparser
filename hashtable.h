#ifndef project_hashtable_h
#define project_hashtable_h


#define CAPACITY 20

typedef struct {
  char* key;
  char* value;
} HashTableItem;

typedef struct {
  int size;
  int count;
  HashTableItem** items;
} HashTable;

unsigned long hash_function(char* str);
HashTableItem* create_item(char* key, char* value);
HashTable* create_table(int size);
void insert(HashTable* table, char* key, char* value);
HashTableItem* search(HashTable* table, char* key);
void free_item(HashTableItem* item);
void free_table(HashTable* table);


#endif
