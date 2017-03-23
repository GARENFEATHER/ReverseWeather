#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAX_INPUT 1024
#define SENT_LENGTH 23
#define RECV_LENGTH 77
#define SERV_PORT 4321
#define DST_ADDR "114.212.191.33"

int sockfd;
struct sockaddr_in servaddr;
int availableCity=6,availableWeather=5;
char *cities[]={"nanjing", "beijing", "haikou", "shanghai", "xiamen", "xian"};
char *weathers[]={"rain", "fog", "cloudy", "clear", "shower"};

void welcome() {
	printf("Welcome to NJUCS Weather Forecast Demo Program!\n");
	printf("Please input City Name in Chinese pinyin(e.g. nanjing or beijing)\n");
	printf("(c)cls,(#)exit\n");
}

void query() {
	printf("Please enter the given number to query\n");
	printf("1.today\n");
	printf("2.three days from today\n");
	printf("3.custom day by yourself\n");
	printf("(r)back,(c)cls,(#)exit\n");
	printf("===================================================\n");
}

int realCity(char *cityInput) {
	int i,j,k;
	for(i=0;i<availableCity;i++) {
		for(j=0,k=0;k<strlen(cities[i]);j++,k++)
			if(cityInput[j] != cities[i][k]) break;
		if(k == strlen(cities[i])) return 1;
	}
	return 0;
}

int commandCheck(char *queryInput, char mode) {
	if(strlen(queryInput) != 1) return 0;
	if(mode == 'b' && queryInput[0] == 'r') return 1;
	if(queryInput[0] == '#') exit(0);
	else if(queryInput[0] == 'c') {
		system("clear");
		return 1;
	}
	return 0;
}

void threeDays(char *cityInput) {
	int weatherNumber=4,tempNumber=4;
	printf("City: %s  Today is: 2017/03/23  Weather information is as follows:\n", cityInput);
	//random
	printf("The 1th day's Weather is: %s;  Temp:%d\n", weathers[weatherNumber], tempNumber);
	//random
	printf("The 2th day's Weather is: %s;  Temp:%d\n", weathers[weatherNumber], tempNumber);
	//random
	printf("The 3th day's Weather is: %s;  Temp:%d\n", weathers[weatherNumber], tempNumber);

}

void oneDay(char *cityInput, int number) {
	int weatherNumber=4,tempNumber=4;
	//random
	printf("City: %s  Today is: 2017/03/23  Weather information is as follows:\n", cityInput);
	if(number == 1) printf("Today's Weather is: %s;  Temp:%d\n", weathers[weatherNumber], tempNumber);
	else printf("The %dth day's Weather is: %s;  Temp:%d\n", number, weathers[weatherNumber], tempNumber);
}

void processQuery(char *cityInput,char *queryInput) {
	char sendline[MAX_INPUT],recvline[MAX_INPUT];
	if(strlen(queryInput) == 1) {
		if(queryInput[0] == '1') sendAndRecv(sendline, cityInput, 2, 1, 1, recvline, 1);
		else if(queryInput[0] == '2') sendAndRecv(sendline, cityInput, 2, 2, 3, recvline, 3);
		else if(queryInput[0] == '3') {
			while(1) {
				printf("Please enter the day number(below 10, e.g. 1 means today):");
				scanf("%s",queryInput);
				int day=(strlen(queryInput) == 1) ? (queryInput[0]-'0') : -1;
				if(day < 10 && day >= 1) {
					sendAndRecv(sendline, cityInput, 2, 1, day, recvline, day);
					break;
				} else printf("input error\n");
			}
		}  else printf("input error!\n");
	} else printf("input error!\n");
}

void initConnection() {
	int result;
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr,  0,  sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(DST_ADDR);
	servaddr.sin_port=htons(SERV_PORT);

	setTimeOut(5);
	result=connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(result == -1) {
		printf("Can Not Connect To Server %s\n", DST_ADDR);
		exit(0);
	}
}

void segmentConstruction(char *sendline, char *content, int type, int mode, int day) {
	int i,k;
	sendline[0]=type;
	sendline[1]=mode;
	for(i=2,k=0;k<strlen(content);i++,k++)
		sendline[i]=content[k];
	for(;i<SENT_LENGTH;i++)
		sendline[i]=0x00;
	sendline[SENT_LENGTH-1]=day;
}

int segmentAnaly(char *recvline, int day) {
	char cityInput[MAX_INPUT];
	int i,k;
	if(recvline[0] == 0x01) return 1;
	else {
		for(i=2,k=0;recvline[i] != 0x00;i++,k++)
			cityInput[k]=recvline[i];
		cityInput[k]='\0';
		if(recvline[0] == 0x04) printf("Sorry, no given day's weather information for city %s!\n", cityInput);
		else {
			if(recvline[1] == 0x42) threeDays(cityInput);
			else if(recvline[1] == 0x41) oneDay(cityInput, day);
		}
	}
	return 0;
}

int sendAndRecv(char *sendline, char *content, int type, int mode, int sentDay, char *recvline, int recvDay) {
	int result=0;
	segmentConstruction(sendline, content, type, mode, sentDay);
	send(sockfd, sendline, SENT_LENGTH, 0);
	result=recv(sockfd, recvline, MAX_INPUT, 0);
	if(result == 0) {
		perror("The server terminated prematurely");
		exit(4);
	} else if(result == -1) {
		if(errno == EINPROGRESS) printf("Receive Data From Server %s Failed!\n", DST_ADDR);
	}
	else result=segmentAnaly(recvline, recvDay);
	return result;
}

void setTimeOut(int time) {
	int ret;
	struct timeval timeout;
	timeout.tv_sec = time;  
    timeout.tv_usec = 0;
    socklen_t len = sizeof(timeout);
    ret=setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
    if(ret == -1) {
    	printf("set send timeout failed!\n");
    	exit(0);
    }
    ret=setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, len);
    if(ret == -1) {
    	printf("set receive timeout failed!\n");
    	exit(0);
    }
}

int main(int argc, char const *argv[])
{
	char cityInput[MAX_INPUT],queryInput[MAX_INPUT],sendline[MAX_INPUT],recvline[MAX_INPUT];
	initConnection();
	system("clear");
	while(1) {
		welcome();
		scanf("%s",cityInput);
		if(commandCheck(cityInput, 'a')) continue;
		if(realCity(cityInput)) {
			sendAndRecv(sendline, cityInput, 1, 0, 0, recvline, 1);
			system("clear");
			query();
			while(1) {
				scanf("%s",queryInput);
				if(commandCheck(queryInput, 'b')) {
					system("clear");
					break;
				}
				processQuery(cityInput, queryInput);
			}
		} else printf("Sorry, Server does not have weather information for city %s!\n", cityInput);
	}
	return 0;
}