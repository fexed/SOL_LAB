#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108
#define MAXTHREADS 10
#define SOCKETNAME "./calzino"
#define BUFFSIZE 100

int skt;
pthread_t capthreadid[MAXTHREADS];

static void* capitolatore(void* arg) {
	int skt_accepted = (int *) arg;
	int i;
	char buff[BUFFSIZE];

	do {
		read(skt_accepted, buff, BUFFSIZE);
		for (i = 0; i < BUFFSIZE; i++) {
			buff[i] = toupper(buff[i]);
		}
		write(skt_accepted, buff, BUFFSIZE);
	} while (strcmp(buff, "exit") != 0);

	close(skt_accepted);
	pthread_exit(NULL);
}

static void gestInt(int signum) {
	int i;
	if (signum == 2) {
		write(1, "Chiudo per SIGINT", 18);
		close(skt);
		for (i = 0; i < MAXTHREADS; i++) {
			pthread_join(capthreadid[i], NULL);
		}
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char *argv[]) {
	int value, skt_accepted, i;
	char buff[BUFFSIZE];
	struct sockaddr_un skta;
	struct sigaction s;

	memset(&s, 0, sizeof(s));
	s.sa_handler = gestInt;
	sigaction(SIGINT, &s, NULL);
	sigaction(SIGPIPE, &s, NULL);

	strncpy(skta.sun_path, SOCKETNAME, UNIX_PATH_MAX);
	skta.sun_family = AF_UNIX;
	skt = socket(AF_UNIX, SOCK_STREAM, 0);

	bind(skt, (struct sockaddr *)&skta, sizeof(skta)); //cast necessario perché struct sockaddr* è tipo generico
	write(1, "Server in ascolto\n", 18);
	do {
		listen(skt, SOMAXCONN);
		skt_accepted = accept(skt, NULL, 0);
		i = 0;
		while(capthreadid[i] != NULL && i < MAXTHREADS) i++;
		if (i < MAXTHREADS) {
			printf("Creato thread %d\n", i);
			pthread_create(&capthreadid[i], NULL, *capitolatore, skt_accepted);
		}
		else close(skt_accepted);
	} while (1);

	close(skt);
	for (i = 0; i < MAXTHREADS; i++) {
		pthread_join(capthreadid[i], NULL);
	}
	return 0;
}