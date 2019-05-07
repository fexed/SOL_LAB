#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int buffersize = 256;
	char *buffer;
	int filein, fileout;	

	if (argc < 3 || argc > 4) {
		printf("usage: %s filein fileout [buffersize]\n", argv[0]);
		return -1;
	}

	if (argc == 4) buffersize = atoi(argv[3]);
	buffer = malloc(buffersize*sizeof(char));

	filein = open(argv[1], O_RDONLY);
	//CHECK_PTR(filein, argv[1]);

	fileout = open(argv[2], O_WRONLY|O_CREAT, 0600);
	//CHECK_PTR(fileout, argv[2]);

	while (read(filein, buffer, buffersize) > 0) {
		write(fileout, buffer, buffersize);
	}

	free(buffer);
	close(filein);
	close(fileout);

	return 0;
}