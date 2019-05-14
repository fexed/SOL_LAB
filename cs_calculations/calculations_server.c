#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#define UNIX_PATH_MAX 108
#define SOCKETNAME "./calzino"
#define BUFFSIZE 100

int main(int argc, char *argv[]) {
	int skt, skt_accepted;
	char buff[BUFFSIZE];
	struct sockaddr_un skta;

	strncpy(skta.sun_path, SOCKETNAME, UNIX_PATH_MAX);
	skta.sun_family = AF_UNIX;
	skt = socket(AF_UNIX, SOCK_STREAM, 0);

	bind(skt, (struct sockaddr *)&skta, sizeof(skta)); //cast necessario perché struct sockaddr* è tipo generico
	listen(skt, SOMAXCONN);
	skt_accepted = accept(skt, NULL, 0);
	read(skt_accepted, buff, BUFFSIZE);
	printf("Server riceve: %s\n", buff);
	write(skt_accepted, "Sayoonara!", 11);
	close(skt);
	close(skt_accepted);
	return 0;
}