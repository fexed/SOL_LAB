#include <stdio.h>
#include <stdlib.h>

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


int main(int argc, char *argv[]) {
	int buffersize = 256;
	char *buffer;
	FILE *filein, *fileout;	

	if (argc < 3 || argc > 4) {
		printf("usage: %s filein fileout [buffersize]\n", argv[0]);
		return -1;
	}

	if (argc == 4) buffersize = atoi(argv[3]);
	buffer = malloc(buffersize*sizeof(char));

	filein = fopen(argv[1], "r");
	CHECK_PTR(filein, argv[1]);

	fileout = fopen(argv[2], "w");
	CHECK_PTR(fileout, argv[2]);

	while (fread(buffer, sizeof(char), buffersize, filein) > 0) {
		fwrite(buffer, sizeof(char), buffersize, fileout);
	}

	free(buffer);
	fclose(filein);
	fclose(fileout);

	return 0;
}