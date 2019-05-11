#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#define CHECK_VALUE(value, name) \
	if (value != 0) { \
		printf("Errore creazione thread %s\n", name); \
	}

#define CHECK_PTR(pntr, string) \
	if (pntr == NULL) { \
		perror(string); \
	}

//static pthread_mutex_t LTmutex = PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t TUmutex = PTHREAD_MUTEX_INITIALIZER;

static void* lettore(void* arg) {
	char* filename = (char*) arg;
	char* buff;
	int pipe;
	FILE* inputfile;

	pipe = open("LT_pipe", O_RDWR);
	if (pipe == -1) {
		printf("L\terror opening LT_pipe\n");
		pthread_exit(NULL);
	} else printf("L\tLT_pipe opened\n");

	printf("L\treading %s\n", filename);
	inputfile = fopen(filename, "r");
	CHECK_PTR(inputfile, filename);

	printf("L\tready\n");
	buff = malloc(1024*sizeof(char));
	buff = fgets(buff, 1024, inputfile);
	while(buff != NULL) {
		//pthread_mutex_lock(&LTmutex);
		write(pipe, buff, 1024);
		//pthread_mutex_unlock(&LTmutex);
		buff = fgets(buff, 1024, inputfile);
	}

	fclose(inputfile);
	close(pipe);
}

static void* tokenizzatore(void* arg) {
	char* buff, *word;
	int result;
	int pipeLT, pipeTU;

	pipeLT = open("LT_pipe", O_RDWR);
	if (pipeLT == -1) {
		printf("T\terror opening LT_pipe\n");
		pthread_exit(NULL);
	} else printf("T\tLT_pipe opened\n");

	pipeTU = open("TU_pipe", O_RDWR);
	if (pipeTU == -1) {
		printf("T\terror opening TU_pipe\n");
		pthread_exit(NULL);
	} else printf("T\tTU_pipe opened\n");


	printf("T\tready\n");
	buff = malloc(1024*sizeof(char));
	do {
		//pthread_mutex_lock(&LTmutex);
		result = read(pipeLT, buff, 1024);
		//pthread_mutex_unlock(&LTmutex);
		word = malloc(30*sizeof(char));
		word = strtok(buff, " .,\n");
		while (word != NULL) {
			write(pipeTU, word, 30);
			word = strtok(NULL, " .,\n");
		}
	} while(result > 0);
	close(pipeLT);
	close(pipeTU);
}

static void* univocatore(void* arg) {
	char* buff;
	int result;
	int pipe;
	pipe = open("TU_pipe", O_RDWR);
	if (pipe == -1) {
		printf("U\terror opening TU_pipe\n");
		pthread_exit(NULL);
	} else printf("U\tTU_pipe opened\n");


	printf("U\tready\n");

	buff = malloc(1024*sizeof(char));
	do {
		//pthread_mutex_lock(&LTmutex);
		result = read(pipe, buff, 30);
		//pthread_mutex_unlock(&LTmutex);
		printf("U\tread: %s\n", buff);

	} while(result > 0);
	close(pipe);
}

int main (int argc, char* argv[]) {
	int value;
	pthread_t Lid, Tid, Uid;

	if (argc != 2) {
		printf("usage: %s inputfile\n", argv[0]);
		return -1;
	} else {
		printf("Using %s\n", argv[1]);
	}

	if ((mkfifo("LT_pipe", 0664) == -1) && errno != EEXIST) {printf("Errore creazione pipe L->T\n");}
	if ((mkfifo("TU_pipe", 0664) == -1) && errno != EEXIST) {printf("Errore creazione pipe T->U\n");}

	value = pthread_create(&Lid, NULL, *lettore, argv[1]);
	CHECK_VALUE(value, "Lettore");
	value = pthread_create(&Tid, NULL, *tokenizzatore, NULL);
	CHECK_VALUE(value, "Tokenizzatore");
	value = pthread_create(&Uid, NULL, *univocatore, NULL);
	CHECK_VALUE(value, "Univocatore");

	pthread_join(Lid, NULL);
	pthread_join(Tid, NULL);
	pthread_join(Uid, NULL);
	return 0;
}