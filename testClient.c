#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define SERV_PORT 4321
#define MAXLINE 4096

int main() {
	int sockfd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE],recvline[MAXLINE];

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr, 0, sizeof(servaddr), 0);
	servaddr.sin_family=AF_INET
	servaddr.sin_addr.s_addr=inet_addr()
}
