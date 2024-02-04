#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "hashtable.h"


unsigned long hash_function(char* str) {
  unsigned long i = 0;

  for (int j = 0; str[j]; j++)
    i += str[j];

  return i % CAPACITY;
}


HashTableItem* search(HashTable* table, char* key) {
  int index = hash_function(key);
  HashTableItem* item = table->items[index];

  if (item != NULL)
    return item;

  return NULL;
}


HashTable* create_table(int size) {
  HashTable* table = (HashTable*) malloc(sizeof(HashTable));
  table->size = size;
  table->count = 0;
  table->items = (HashTableItem**) calloc(table->size, sizeof(HashTableItem*));

  for (int i = 0; i < table->size; i++)
    table->items[i] = NULL;

  return table;
}


HashTableItem* create_item(char* key, char* value) {
  HashTableItem* item = (HashTableItem*) malloc(sizeof(HashTableItem));
  item->key = (char*) malloc(strlen(key) + 1);
  item->value = (char*) malloc(strlen(value) + 1);
  strcpy(item->key, key);
  strcpy(item->value, value);
  return item;
}


void insert(HashTable* table, char* key, char* value) {
  HashTableItem* item = create_item(key, value);
  int index = hash_function(key);

  HashTableItem* current_item = table->items[index];
  if (current_item == NULL) {
    if (table->count == table->size) {
      printf("Insert Error: Hash Table is full\n");
      free_item(item);
      return;
    }

    table->items[index] = item;
    table->count++;
  }
}


void free_item(HashTableItem* item) {
  free(item->key);
  free(item->value);
  free(item);
}


void free_table(HashTable* table) {
  for (int i = 0; i < table->size; i++) {
    HashTableItem* item = table->items[i];

    if (item != NULL)
      free_item(item);
  }

  free(table->items);
  free(table);
}


void print_table(HashTable* table) {
  for (int i = 0; i < table->size; i++) {
    HashTableItem* item = table->items[i];

    if (item != NULL)
      printf("Key: %s, Value: %s\n", item->key, item->value);
  }
}
