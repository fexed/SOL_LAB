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
	printf("SIGINT ricevuti: %d", sigintcounter);
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

	do {
		sleep(1);
	} while(sigstpcounter < 3);

	printf("Premi un tasto per far continuare il programma\n");

	return 0;
}