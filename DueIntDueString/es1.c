#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
	if (argc != 5) {
		printf("Errore: inserire 2 interi seguiti da 2 stringhe\n");
		return -1;
	}
	printf("%s, %s, %s, %s\n", argv[1], argv[2], argv[3], argv[4]);
	printf("%s", envp[1]);
	return 0;
}
