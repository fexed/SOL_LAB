#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCH 1024

char* reverse(char* toreverse) {
	char* reversed = malloc(sizeof(toreverse));
	char *p1, *p2;
      if (! toreverse || ! *toreverse)
            return toreverse;
      for (p1 = toreverse, p2 = toreverse + strlen(toreverse) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return toreverse;
}

int main(int argc, char *argv[]) {
	FILE *filein, *fileout;
	if (argc < 3 || argc > 4) {
		printf("usage: %s filein fileout [append]\n", argv[0]);
		return -1;
	}

	filein = fopen(argv[1], "r");
	if (argc == 4 && (strcmp(argv[3], "a") == 0)) {
		fileout = fopen(argv[2], "a");
	} else {
		fileout = fopen(argv[2], "w");
	}
	
	char* buf = malloc(MAXCH*sizeof(char));
	while (fgets(buf, MAXCH, filein)) {
		fprintf(fileout, "%s\n", strtok(reverse(buf), "\n"));
	}
	free(buf);

	return 0;
}