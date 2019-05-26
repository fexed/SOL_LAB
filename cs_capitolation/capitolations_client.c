#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108
#define SOCKETNAME "./calzino"
#define BUFFSIZE 100

int main(int argc, char *argv[]) {
	int skt, i;
	char buff[BUFFSIZE];
	struct sockaddr_un skta;

	if (argc < 2) {
		printf("usage: %s str1 [str2 ...]\n", argv[0]);
		return -1;
	}

	strncpy(skta.sun_path, SOCKETNAME, UNIX_PATH_MAX);
	skta.sun_family = AF_UNIX;
	skt = socket(AF_UNIX, SOCK_STREAM, 0);

	while(connect(skt, (struct sockaddr*)&skta, sizeof(skta)) == -1) {
		if (errno == ENOENT) sleep(1); //socket non esiste
		else return -1;
	}

	for (i = 1; i < argc; i++) {
		write(skt, argv[i], BUFFSIZE);
		printf("%s\t->\t", argv[i]);
		read(skt, buff, BUFFSIZE);
		printf("%s\n", buff);
	}
	write(skt, "exit", BUFFSIZE);
	close(skt);
	return 0;
}