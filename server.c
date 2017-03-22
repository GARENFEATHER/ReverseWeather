#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096
#define SERV_PORT 4321
#define LISTENQ 8

int main(int argc, char const *argv[])
{
	int listenfd, connfd, n, pid;
	socklen_t clilen;
	char buf[MAXLINE];
	struct sockaddr_in cliaddr, servaddr;

	listenfd=socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(SERV_PORT);

	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);
	printf("server running...\n");
	for(;;) {
		clilen=sizeof(cliaddr);
		connfd=accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		printf("%s\n", "Received request...");

		pid=fork();
		if(pid == 0) {
			printf("%s\n", "Child created for dealing with clilent ");
			close(listenfd);
			while(1) {
                n == recv(connfd, buf, MAXLINE, 0);
                printf("%d\n", n);
                if(n <= 0) break;
				printf("%s\n", "String receivrd from and resent to the client");
				puts(buf);
				send(connfd, buf, n, 0);
				memset(buf, 0, MAXLINE);
			}
			if(n<0) {
				printf("%s\n", "read error");
				exit(0);
			}
			close(connfd);
            exit(0);
		} else if(pid < 0) {
			printf("error!\n");
			return 0;
		} else waitpid(pid,NULL,0);
	}
	return 0;
}
