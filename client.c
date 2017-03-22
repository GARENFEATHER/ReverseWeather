#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096
#define SERV_PORT 4321

int main(int argc, char const *argv[])
{
	int sockfd, tmp;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], recvline[MAXLINE];

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr,  0,  sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(SERV_PORT);

	tmp=connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("%d\n", tmp);
	while(fgets(sendline, MAXLINE, stdin) != NULL) {
		tmp=send(sockfd, sendline, strlen(sendline), 0);
        printf("%d\n",tmp);
		if(recv(sockfd, recvline, MAXLINE, 0) == 0) {
			perror("The server terminated prematurely");
			exit(4);
		}
		printf("%s", "String received from the server: ");;
		fputs(recvline, stdout);

		memset(sendline, 0, MAXLINE);
		memset(recvline, 0, MAXLINE);
	}
	return 0;
}
