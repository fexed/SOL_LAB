#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct list {
	char* word;
	struct list* next;
} list_t;

list_t *createList();

int destroyList(list_t *L);

int insertList(list_t *L, const char *str);

void printList(list_t *L);