#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define CHECK_VALUE(value, name) \
	if (value != 0) { \
		printf("Errore creazione thread %s\n", name); \
	}

#define CHECK_PTR(pntr, string) \
	if (pntr == NULL) { \
		perror(string); \
	}

static int LT_pfd[2], TU_pfd[2];
//[1] scrittura, [0] lettura
static pthread_mutex_t LTmutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t TUmutex = PTHREAD_MUTEX_INITIALIZER;

static void* lettore(void* arg) {
	char* filename = (char*) arg;
	char* buff;
	FILE* inputfile;

	printf("L\treading %s\n", filename);
	inputfile = fopen(filename, "r");
	CHECK_PTR(inputfile, filename);

	buff = malloc(1024*sizeof(char));
	buff = fgets(buff, 1024, inputfile);
	while(buff != NULL) {
		//pthread_mutex_lock(&LTmutex);
		write(LT_pfd[1], buff, sizeof(buff));
		//pthread_mutex_unlock(&LTmutex);
		buff = fgets(buff, 1024, inputfile);
	}

	fclose(inputfile);
	close(LT_pfd[1]);
}

static void* tokenizzatore(void* arg) {
	char* buff;
	int result;

	printf("T\tready\n");
	buff = malloc(1024*sizeof(char));
	do {
		//pthread_mutex_lock(&LTmutex);
		result = read(LT_pfd[0], buff, 1024);
		//pthread_mutex_unlock(&LTmutex);
		printf("%s", buff);
	} while(result > 0);
	close(LT_pfd[0]);
}

static void* univocatore(void* arg) {
	printf("U\tready\n");

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

	if (pipe(LT_pfd) == -1) { printf("Errore creazione pipe L->T\n");}
	if (pipe(TU_pfd) == -1) { printf("Errore creazione pipe T->U\n");}

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