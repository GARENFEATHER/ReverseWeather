#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 4096
#define SERV_PORT 4321

typedef unsigned char Byte;

int main(int argc, char const *argv[])
{
	Byte message[23];
	char city[]="nanjing";
	int i,k,int sockfd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE], recvline[MAXLINE];
	char src[]="114.212.191.33";

	message[0]=0x01;
	message[1]=0x00;
	for(i=2,k=0;k<strlen(city);i++,k++) 
		message[i]=city[k];
	for(;i<23;i++)
		message[i]=0x00;

	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr,  0,  sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(src);
	servaddr.sin_port=htons(SERV_PORT);

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	send(sockfd, message, strlen(message), 0);
	if(recv(sockfd, recvline, MAXLINE, 0) == 0) {
		perror("The server terminated prematurely");
		exit(4);
	}
	printf("%s", "String received from the server: ");
	fputs(recvline, stdout);
	return 0;
}