#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHECK_PTR(pntr, string) \
	if (pntr == NULL) { \
		perror(string); \
		return -1; \
	}

#define CHECK_RESULT(res) \
	if (result == EOF || result == 0) { \
		perror("result"); \
		return -1; \
	}

int confronta(int (*compara)(const void*, const void*, size_t), float* firstMatrix, float* secondMatrix, int size) {
	int i, j, result;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			result = compara(&firstMatrix[(i*size)+j], &secondMatrix[(i*size)+j], sizeof(float));
			if (result != 0) return i;
		}
	}

	return -1;
}

int main(int argc, char* argv[]) {
	FILE *txtfile, *datfile;
	float *M1, *M2;
	int N, i, j, result;

	if (argc < 3) {
		printf("usage: %s matdump.txt matdump.dat\n", argv[0]);
		return -1;
	}

	txtfile = fopen(argv[1], "r");
	CHECK_PTR(txtfile, "matdump.txt");
	datfile = fopen(argv[2], "r");
	CHECK_PTR(datfile, "matdump.dat");

	result = fscanf(txtfile, "%d\n", &N);
	CHECK_RESULT(result);
	M1 = (float*) malloc(N*N*sizeof(float));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			result = fscanf(txtfile, "%f", &(M1[(i*N)+j]));
			CHECK_RESULT(result);
		}
	}
	fclose(txtfile);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%.2f\t", M1[(i*N)+j]);
		}
		printf("\n");
	}

	printf("\n");

	fread(&N, sizeof(int), 1, datfile);
	M2 = (float*) malloc(N*N*sizeof(float));
	fread(M2, sizeof(float), N*N, datfile);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%.2f\t", M2[(i*N)+j]);
		}
		printf("\n");
	}
	fclose(datfile);

	result = confronta(memcmp, M1, M2, N);
	if (result == -1) {
		printf("Le due matrici sono identiche!\n");
	} else printf("Le due matrici sono diverse sulla riga %d\n", result);

	free(M1);
	free(M2);

	return 0;
}