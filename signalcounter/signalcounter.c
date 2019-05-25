#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int sigintcounter = 0;
int sigstpcounter = 0;

static void sigintgestore(int signum) {
	sigintcounter += 1;
}

static void sigstpgestore(int signum) {
	sigstpcounter += 1;
}

int main() {
	struct sigaction sig_stop;
	struct sigaction sig_int;
	
	memset(&sig_stop, 0, sizeof(sig_stop));
	memset(&sig_int, 0, sizeof(sig_int));
	sig_stop.sa_handler = sigstpgestore;
	sig_int.sa_handler = sigintgestore;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGTSTP, &sig_stop, NULL);

	printf("SIGINT\tSIGTSTP\n\n");
	do {
		sleep(1);
		printf("%d\t%d\n", sigintcounter, sigstpcounter);
	} while(sigintcounter < 3);

	return 0;
}