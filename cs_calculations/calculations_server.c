#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108
#define SOCKETNAME "./calzino"
#define BUFFSIZE 100

#define CHECK_VALUE(value, name) \
	if (value != 0) { \
		printf("Errore creazione thread %s\n", name); \
	}

static void* calcolatore(void* arg) {
	char* program = calloc(BUFFSIZE, sizeof(char));
	program = strcpy(program, "echo \"");
	program = strcat(program, (char *) arg);
	program = strcat(program, "\" | bc > output");
	//strcat(strcat("echo \"", (char*) arg), "\" | bc > output"); 
	system(program);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int skt, skt_accepted, value;
	char buff[BUFFSIZE];
	struct sockaddr_un skta;
	pthread_t calcthreadid;
	FILE* outputfile;

	strncpy(skta.sun_path, SOCKETNAME, UNIX_PATH_MAX);
	skta.sun_family = AF_UNIX;
	skt = socket(AF_UNIX, SOCK_STREAM, 0);

	bind(skt, (struct sockaddr *)&skta, sizeof(skta)); //cast necessario perché struct sockaddr* è tipo generico
	do {
		listen(skt, SOMAXCONN);
		skt_accepted = accept(skt, NULL, 0);
		do {
			read(skt_accepted, buff, BUFFSIZE);
			if (strcmp(buff, "exit") != 0) {
				printf("Server riceve: %s\n", buff);
				value = pthread_create(&calcthreadid, NULL, *calcolatore, buff);
				if (value != 0) {
					printf("Errore creazione thread calcolatore\n");
					write(skt_accepted, "Errore creazione thread calcolatore", 36);
				} else {
					pthread_join(calcthreadid, NULL);
					outputfile = fopen("output", "r");
					if (outputfile == NULL) {
						printf("Errore apertura file output");
						write(skt_accepted, "Errore apertura file output", 28);
					} else {
						fread(buff, BUFFSIZE, sizeof(char), outputfile);
						fclose(outputfile);
						write(skt_accepted, buff, BUFFSIZE);
					}
				}
			}
		} while (strcmp(buff, "exit") != 0);
		close(skt_accepted);
	} while (1);	
	close(skt);
	return 0;
}