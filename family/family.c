#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
	int n, pid, i, j;
	if (argc != 2) {
		printf("usage: %s n\n", argv[0]);
		return 0;
	}

	n = atoi(argv[1]);

	if (n >= 0) {
		for (; n >= 0; n--) {
			if (n > 0) {
				for (j = 0; j < n; j++) printf("-");
				printf(" %d: creo un processo figlio\n", getpid());
				pid = fork();
				if (pid != 0) {
					waitpid(pid);
					for (j = 0; j < n; j++) printf("-");
					printf(" %d: terminato con successo\n", getpid());
					return 0;
				}
			} else {
				printf("%d: sono l'ultimo discendente\n", getpid());
				printf("%d: terminato con successo\n", getpid());
				return 0;
			}
		}
	} else {
		printf("n deve essere positivo\n");
		return -1;
	}

	return 0;
}