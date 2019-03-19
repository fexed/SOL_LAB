#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libList.h"

#define CHECK_PTR(pntr, string) \
	if (pntr == NULL) { \
		perror(string); \
		return -1; \
	}

#define CHECK_RESULT(res) \
	if (result == EOF || result == 0) { \
		perror("result"); \
		return -1; \
	}

int main (int argc, char* argv[]) {
	FILE *inputfile;
	list_t *lst;
	char *buff;
	int result;

	if (argc < 2) {
		printf("usage: %s file\n", argv[0]);
		return -1;
	}

	inputfile = fopen(argv[1], "r");
	CHECK_PTR(inputfile, argv[1]);

	lst = createList();
	buff = malloc(1024*sizeof(char));
	result = fscanf(inputfile, "%s ", buff);
	CHECK_RESULT(result);
	while(result != EOF) {
		insertList(lst, buff);
		result = fscanf(inputfile, "%s ", buff);
	}

	printList(lst);
	printf("\n");
	destroyList(lst);
	fclose(inputfile);
	return 0;
}