#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define CAPACITY 512 // Size of hash table

unsigned long hash_function(char * str){
	unsigned long i = 0;
	for (int j = 0; str[j]; j++) {
		i += str[j];
	}
	return i % CAPACITY;
}
typedef struct Ht_item Ht_item;

// Define the Hash Table Item here
struct Ht_item {
    char* key;
    int value;
};

typedef struct HashTable HashTable;

// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
};

Ht_item* create_item(char* key, int value) {
	Ht_item*  item = (Ht_item*) malloc (sizeof(Ht_item));
	item->key = (char*) malloc (strlen(key) + 1);
	item->value = 0; 

	strcpy(item->key, key);
	item->value = value;

	return item;
}

HashTable* create_table(int size) {
	HashTable* table = (HashTable*)malloc(sizeof(HashTable));
	table->size = size;
	table->count = 0;
	table->items = (Ht_item**)calloc(table->size, sizeof(Ht_item*));
	for (int i = 0; i < table->size; ++i) {
		table->items[i] = NULL;
	}
	return table;
}

void free_item(Ht_item* item) {
	free(item->key);
	free(item);
}

void free_table(HashTable* table) {
	for (int i = 0; i < table->size; ++i) {
		Ht_item* item = table->items[i];
		if (item != NULL) {
			free_item(item);
		}
	}
	free(table->items);
	free(table);
}
void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
}

void ht_insert(HashTable* table, char* key, int value) {
	Ht_item* item = create_item(key, value);

	unsigned long index = hash_function(key);

	Ht_item* current_item = table->items[index];

	if (current_item == NULL) {

		if (table->count == table->size) {
			printf("Insert Error: HashTable is Full\n");
			free_item(item);
			return;
		}
		table->items[index] = item;
		table->count++;
	} else {
		if (strcmp(current_item->key, key) == 0) {
			current_item->value = value;
			return;
		} else { // Коллизия
			 handle_collision(table, index, item);
			return;			
		}
	}


}

int ht_search(HashTable* table, char* key) {
	int index = hash_function(key);
	Ht_item* item = table->items[index];

	if (item != NULL) {
		if (strcmp(item->key, key) == 0) {
			return item->value;
		}
	}
	return -1;
}

void print_search(HashTable* table, char* key) {
	int val;
	if ((val = ht_search(table, key)) == -1) {
		printf("Key: %s doesn't exist\n", key);
		return;
	} else {
		printf("Key: %s, Value: %d\n", key, val);
	}
}

void print_table(HashTable* table) {
	printf("\nHash Table\n--------------------\n");
	for (int i = 0; i < table->size; ++i) {
		if (table->items[i]) {
			printf("Index:%d, Key:%s, Value:%d\n", i, table->items[i]->key, table->items[i]->value);
		}
	}
	printf("--------------------\n");
}

#endif