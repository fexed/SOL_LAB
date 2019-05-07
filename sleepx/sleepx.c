#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	int n;
	if (argc != 2) {
		printf("usage: %s n\n", argv[0]);
		return -1;
	}
	n = atoi(argv[1]);

	if (fork() == 0) {
		setsid();
		sleep(n);
		printf("%d\n", (int)getpid());
		printf("%d\n", (int)getppid());
	} else {
		return 0;
	}
	return 0;
}