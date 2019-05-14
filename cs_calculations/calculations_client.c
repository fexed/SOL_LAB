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
	int skt;
	char buff[BUFFSIZE];
	struct sockaddr_un skta;

	strncpy(skta.sun_path, SOCKETNAME, UNIX_PATH_MAX);
	skta.sun_family = AF_UNIX;
	skt = socket(AF_UNIX, SOCK_STREAM, 0);

	while(connect(skt, (struct sockaddr*)&skta, sizeof(skta)) == -1) {
		if (errno == ENOENT) sleep(1); //socket non esiste
		else return -1;
	}

	write(skt, "Hello world dal client attraverso il calzino", 45);
	read(skt, buff, BUFFSIZE);
	printf("Client riceve: %s\n", buff);
	close(skt);
	return 0;
}