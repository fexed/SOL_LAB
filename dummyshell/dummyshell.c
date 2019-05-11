#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	char* command = malloc(sizeof(char));
	char* next;
	char* arglist[10];
	int i = 1;
	do {
		free(command);
		command = malloc(50*sizeof(char));
		scanf("%s", command);
		if (strcmp(command, "exit") != 0) {
			//int execv(const char *path, char *const argv[]);
			*arglist = malloc(50*sizeof(char));
			arglist[0] = strtok(command, " ");
			do {
				next = strtok(NULL, " ");
				if (next != NULL) {
					arglist[i] = next;
					i++;
				}
			} while (next != NULL);
			execv("/", arglist);
		}
	} while (strcmp(command, "exit") != 0);

	return 0;
}