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

#define BUFFSIZE 512
#define WORDSIZE 16

//static pthread_mutex_t LTmutex = PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t TUmutex = PTHREAD_MUTEX_INITIALIZER;

static void* lettore(void* arg) {
	char* filename = (char*) arg;
	char* buff;
	int pipe;
	FILE* inputfile;

	pipe = open("LT_pipe", O_WRONLY);
	if (pipe == -1) {
		printf("L\terror opening LT_pipe\n");
		pthread_exit(NULL);
	} else printf("L\tLT_pipe opened\n");

	printf("L\treading %s\n", filename);
	inputfile = fopen(filename, "r");
	CHECK_PTR(inputfile, filename);

	printf("L\tready\n");
	buff = malloc(BUFFSIZE*sizeof(char));
	buff = fgets(buff, BUFFSIZE, inputfile);
	while(buff != NULL) {
		//pthread_mutex_lock(&LTmutex);
		write(pipe, buff, BUFFSIZE);
		//pthread_mutex_unlock(&LTmutex);
		free(buff);
		buff = malloc(BUFFSIZE*sizeof(char));
		buff = fgets(buff, BUFFSIZE, inputfile);
	}
	free(buff);
	fclose(inputfile);
	close(pipe);
	pthread_exit(NULL);
}

static void* tokenizzatore(void* arg) {
	char* buff, *word;
	int result;
	int pipeLT, pipeTU;

	pipeLT = open("LT_pipe", O_RDONLY);
	if (pipeLT == -1) {
		printf("T\terror opening LT_pipe\n");
		pthread_exit(NULL);
	} else printf("T\tLT_pipe opened\n");

	pipeTU = open("TU_pipe", O_WRONLY);
	if (pipeTU == -1) {
		printf("T\terror opening TU_pipe\n");
		pthread_exit(NULL);
	} else printf("T\tTU_pipe opened\n");


	printf("T\tready\n");
	buff = malloc(BUFFSIZE*sizeof(char));
	do {
		//pthread_mutex_lock(&LTmutex);
		result = read(pipeLT, buff, BUFFSIZE);
		//pthread_mutex_unlock(&LTmutex);
		word = malloc(WORDSIZE*sizeof(char));
		word = strtok(buff, " .,\n");
		while (word != NULL) {
			write(pipeTU, word, WORDSIZE);
			free(word);
			word = malloc(WORDSIZE*sizeof(char));
			word = strtok(NULL, " .,\n");
		}
		free(word);
		free(buff);
		buff = malloc(BUFFSIZE*sizeof(char));
	} while(result > 0);
	free(buff);
	close(pipeLT);
	close(pipeTU);
	pthread_exit(NULL);
}

static void* univocatore(void* arg) {
	char* buff, *words, *temp;
	int result, pipe;
	size_t len1, len2;
	pipe = open("TU_pipe", O_RDONLY);
	if (pipe == -1) {
		printf("U\terror opening TU_pipe\n");
		pthread_exit(NULL);
	} else printf("U\tTU_pipe opened\n");

	words = malloc(sizeof(char));
	printf("U\tready\n");

	buff = malloc(BUFFSIZE*sizeof(char));
	do {
		//pthread_mutex_lock(&LTmutex);
		result = read(pipe, buff, WORDSIZE);
		//pthread_mutex_unlock(&LTmutex);
		//printf("U\tread: %s\n", buff);
		if (strstr(words, buff) == NULL) {
			len1 = strlen(words);
			len2 = strlen(buff);
			temp = malloc(len1+len2+1);
			buff = strcat(buff, "\n");
			memcpy(temp, words, len1);
			memcpy(temp+len1, buff, len2+1);
			//free(words);
			words = malloc(strlen(temp));
			memcpy(words, temp, strlen(temp));
			free(temp);
		}
		free(buff);
		buff = malloc(BUFFSIZE*sizeof(char));
	} while(result > 0);
	free(buff);
	close(pipe);

	printf("%s", words);
	free(words);
	pthread_exit(NULL);
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

	if ((mkfifo("LT_pipe", 0664) == -1) && errno != EEXIST) {printf("Errore creazione pipe LT\n");}
	if ((mkfifo("TU_pipe", 0664) == -1) && errno != EEXIST) {printf("Errore creazione pipe TU\n");}

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