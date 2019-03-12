#include <stdlib.h>
#include <stdio.h>

#define CHECK_PTR(pntr, string) \
	if (pntr == NULL) { \
		perror(string); \
		return -1; \
	}

int main (int argc, char* argv[]) {
	int N, i, j;
	float* M;
	FILE* outfile_txt;
	FILE* outfile_bin;

	if (argc < 2) {
		printf("usage: %s N\n", argv[0]);
		return -1;
	}
	N = strtol(argv[1], NULL, 10);
	M = (float*) malloc(N*N*sizeof(float));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			M[(i*N)+j] = (i+j)/2.0;
			printf("%.2f\t", M[(i*N)+j]);
		}
		printf("\n");
	}

	outfile_txt = fopen("matdump.txt", "w");
	CHECK_PTR(outfile_txt, "outfile_txt");
	outfile_bin = fopen("matdump.dat", "w");
	CHECK_PTR(outfile_bin, "outfile_bin");

	fprintf(outfile_txt, "%d\n", N);
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fprintf(outfile_txt, "%.2f\t", M[(i*N)+j]);
		}
		fprintf(outfile_txt, "\n");
	}
	fclose(outfile_txt);

	fwrite(&N, sizeof(int), 1, outfile_bin);
	fwrite(M, sizeof(float), N*N, outfile_bin);
	fclose(outfile_bin);

	free(M);
	return 0;
}