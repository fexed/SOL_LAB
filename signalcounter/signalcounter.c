#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int sigintcounter = 0;
int sigstpcounter = 0;
char* input;

static void sigalrmgestore(int signum) {
	write(1, "Terminazione\n", 13);
	free(input);
	exit(0);
}

static void sigalrmgestoreignora(int signum) {
}

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
	struct sigaction sig_alrm;
	
	memset(&sig_stop, 0, sizeof(sig_stop));
	memset(&sig_int, 0, sizeof(sig_int));
	memset(&sig_alrm, 0, sizeof(sig_alrm));
	sig_stop.sa_handler = sigstpgestore;
	sig_int.sa_handler = sigintgestore;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGTSTP, &sig_stop, NULL);

	input = malloc(1*sizeof(char)); //per evitare il free inutile subito dopo, hack
	do {
		free(input);
		sig_alrm.sa_handler = sigalrmgestoreignora;
		sigaction(SIGALRM, &sig_alrm, NULL);
		printf("\n\t!!!\n");
		sigstpcounter = 0;
		do {
			sleep(1);
		} while(sigstpcounter < 3);

		printf("Scrivi \"yes\" per far continuare il programma\n");
		alarm(10);
		sig_alrm.sa_handler = sigalrmgestore;
		sigaction(SIGALRM, &sig_alrm, NULL);
		input = calloc(10, sizeof(char));
		scanf("%s", input);
	} while (strcmp(input, "yes") == 0);
	free(input);

	return 0;
}