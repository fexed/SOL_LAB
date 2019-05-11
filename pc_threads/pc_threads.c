#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define CHECK_VALUE(value) \
	if (value != 0) { \
		printf("Errore creazione thread\n"); \
	}

static int buffer;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void* P(void* arg) {
	int slp_time = 1+rand()%2;
	do {
		pthread_mutex_lock(&mutex);
		buffer = rand()%100;
		pthread_mutex_unlock(&mutex);
		sleep(slp_time);
	} while(1);
}

static void* C(void* arg) {
	int slp_time = 1+rand()%2;
	do {
		pthread_mutex_lock(&mutex);
		if (buffer != 0) {
			printf("\t%d\n", buffer);
			buffer = 0;
		}
		pthread_mutex_unlock(&mutex);
		sleep(slp_time);
	} while(1);
}

int main() {
	int value;
	pthread_t Pid, Cid;
	value = pthread_create(&Pid, NULL, *P, NULL);
	CHECK_VALUE(value);
	value = pthread_create(&Cid, NULL, *C, NULL);
	CHECK_VALUE(value);
	pthread_join(Pid, NULL);
	pthread_join(Cid, NULL);
	return 0;
}