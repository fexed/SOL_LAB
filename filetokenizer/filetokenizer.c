#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("usage: %s filein fileout [append]", argv[0]);
		return 0;
	}
}