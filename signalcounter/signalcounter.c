#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int sigintcounter = 0;
int sigstpcounter = 0;

static void* waiter(void* arg) {
	alarm(10);
	pthread_exit(NULL);
}

static void sigalrmgestore(int signum) {
	write(1, "Terminazione", 13);
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
	int value;
	char* input;
	struct sigaction sig_stop;
	struct sigaction sig_int;
	struct sigaction sig_alrm;
	pthread_t waiterpid;
	
	memset(&sig_stop, 0, sizeof(sig_stop));
	memset(&sig_int, 0, sizeof(sig_int));
	memset(&sig_alrm, 0, sizeof(sig_alrm));
	sig_stop.sa_handler = sigstpgestore;
	sig_int.sa_handler = sigintgestore;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGTSTP, &sig_stop, NULL);

	do {
		sig_alrm.sa_handler = sigalrmgestoreignora;
		sigaction(SIGALRM, &sig_alrm, NULL);
		printf("\n\t!!!\n");
		sigstpcounter = 0;
		do {
			sleep(1);
		} while(sigstpcounter < 3);

		printf("Scrivi \"yes\" per far continuare il programma\n");
		value = pthread_create(&waiterpid, NULL, *waiter, NULL);
		sig_alrm.sa_handler = sigalrmgestore;
		sigaction(SIGALRM, &sig_alrm, NULL);
		input = calloc(10, sizeof(char));
		scanf("%s", input);
	} while (strcmp(input, "yes") == 0);
	return 0;
}