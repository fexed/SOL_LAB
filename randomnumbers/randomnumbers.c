#include <stdlib.h>
#include <time.h>

#define N 1000
#define K 15

void main(int argc, char* argv[]) {
	int *numbers = calloc(K, sizeof(int));
	double *C = calloc(N, sizeof(double));
	int i;
	unsigned int *seed = malloc(sizeof(int));
	*seed = time(NULL);
	for (i = 0; i < K; i++) {
		numbers[i] = rand_r(seed)%N;
		printf("%d ", numbers[i]);
	}
	printf("\n\n");

	for (i = 0; i < K; i++) {
		C[numbers[i]]++;
	}

	for (i = 0; i < N; i++) {
		if (C[i] > 0) {
			C[i] = (C[i] * 100)/K;
			printf("%d\t%f\n", i, C[i]);
		}
	}
}