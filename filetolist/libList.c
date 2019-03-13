#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct list {
	char* word;
	struct list* next;
} list_t;

list_t *createList() {
	return malloc(sizeof(list_t));
}

int destroyList(list_t *L) {
	if (L->next != NULL) {
		destroyList(L->next);
		free(L);
	} else {
		free(L);
	}
	return 0;
}

int insertList(list_t *L, const char *str) {
	if (L->word == NULL) {
		L->word = malloc(strlen(str)*sizeof(char));
		strcpy(L->word, str);
		return 0;
	} else {
		int comparison = strcmp(L->word, str);

		if (comparison > 0) {
			list_t *newblock = malloc(sizeof(list_t));
			newblock->word = malloc(strlen(str)*sizeof(char));
			strcpy(newblock->word, str);

			newblock->next = malloc(sizeof(L));
			memcpy(newblock->next, L, sizeof(list_t)); //TODO FIX
			*L = *newblock;
			return 0;
		} else {
			if (L->next == NULL) {
				list_t *newblock = malloc(sizeof(list_t));
				newblock->word = malloc(strlen(str)*sizeof(char));
				strcpy(newblock->word, str);
				L->next = newblock;
				return 0;
			} else return insertList(L->next, str);
		}
	}
}

void printList(list_t *L) {
	printf("[%s] >", L->word);
	if (L->next != NULL) printList(L->next);
}