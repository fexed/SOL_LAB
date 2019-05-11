#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*Scrivere un programma C con due threads,
un produttore (P) ed un consumatore (C).
Il thread P genera, uno alla volta, una sequenza di numeri inserendoli in un buffer
di una sola posizione condiviso con il thread C. Il thread consumatore estrae i
numeri dal buffer e li stampa sullo standard output. Se il buffer e' pieno P
attende che C consumi il dato, analogamente se il buffer e' vuoto C attende
che P produca un valore da consumare.*/

#define CHECK_VALUE(value) \
	if (value != 0) { \
		printf("Errore creazione thread\n"); \
	}

static int* buffer;

static void* P(void* arg) {
	printf("P creato\n");
}

static void* C(void* arg) {
	printf("C creato\n");
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