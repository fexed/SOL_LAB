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
	char* strbuff = "\t\tSIGINT ricevuti: ";
	char* buff = calloc(50, sizeof(char));
	char* numbuff = calloc(10, sizeof(char));
	sprintf(numbuff, "%d\n", sigintcounter);
	buff = strcat(buff, strbuff);
	buff = strcat(buff, numbuff);
	write(1, buff, 25);
	free(buff);
	free(numbuff);
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