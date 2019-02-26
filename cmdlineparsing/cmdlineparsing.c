#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(int argc, char *argv[]) {
	int i;
	char* str = (char*) malloc(sizeof(char)*10);

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-h") == 0) {
			printf("%s -n <numero> -s <stringa> -m <numero> -h\n", argv[0]);
			i = 100;
		} else if (strcmp(argv[i], "-n") == 0) {
			i++;
			str = (char*) realloc(str, sizeof(char)*((sizeof(str)/sizeof(char))+((sizeof(argv[i])/sizeof(char)))));
			strcat(str, argv[i]);
		} else if (strcmp(argv[i], "-m") == 0) {
			i++;
			str = (char*) realloc(str, sizeof(char)*((sizeof(str)/sizeof(char))+((sizeof(argv[i])/sizeof(char)))));
			strcat(str, argv[i]);
		} else if (strcmp(argv[i], "-s") == 0) {
			i++;
			str = (char*) realloc(str, sizeof(char)*((sizeof(str)/sizeof(char))+((sizeof(argv[i])/sizeof(char)))));
			strcat(str, argv[i]);
		}
	}

	if (i < 100) {
		printf("%s", str);
		free(str);
	}
}