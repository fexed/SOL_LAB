#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
	fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
	return -1;
    }

    char** saveptr = malloc(sizeof(char*));
    char* token1 = strtok_r(argv[1], " ", saveptr); //saveptr per poter tokenizzare mentre tokenizzo altra stringa
    char* secondastringa = malloc(sizeof(argv[2]));
    secondastringa = strcpy(secondastringa, argv[2]); //per poter tokenizzare più volte la stessa stringa
    while (token1) {
	printf("%s\n", token1);
	char* token2 = strtok(secondastringa, " ");
	while(token2) {
	    printf("%s\n", token2);
	    token2 = strtok(NULL, " ");
	}
	secondastringa = strcpy(secondastringa, argv[2]);
	token1 = strtok_r(NULL, " ", saveptr);
    }
    free(secondastringa);
    free(saveptr);
    return 0;
}
