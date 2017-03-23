#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 1024
#define SENT_LENGTH 23
#define RECV_LENGTH 77
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
	int i;
	for(i=0;i<availableCity;i++)
		if(cityInput == cities[i]) return 1;
	return 0;
}

//return 
int queryCheck(char *queryInput) {
	//todo
	return 1;
}

int commandCheck(char *queryInput, char mode) {
	if(mode == 'b' && queryInput == "r") return 1;
	if(queryInput == "#") exit(0);
	else if(queryInput == "c") {
		//clear 
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
	if(number>8) printf("Sorry, no given day's weather information for city %s!\n", cityInput);
	else {
		int weatherNumber=4,tempNumber=4;
		//random
		printf("City: %s  Today is: 2017/03/23  Weather information is as follows:\n", cityInput);
		if(number == 1) printf("Today's Weather is: %s;  Temp:%d\n", weathers[weatherNumber], tempNumber);
		else printf("The %dth day's Weather is: %s;  Temp:%d\n",cityInput, number);
	}
}

void processQuery(char *cityInput,char *queryInput) {
	if(strlen(queryInput) == 1) {
		if(queryInput[0] == '1') {
			//send
			oneDay(cityInput, 1);
		} else if(queryInput[0] == '2') {
			//send
			threeDays(cityInput);
		} else if(queryInput[0] == '3') {
			while(1) {
				printf("Please enter the day number(below 10, e.g. 1 means today):");
				scanf("%s",queryInput);
				int day=-1;
				//convert
				if(day < 10 && day > 1) {
					//send
					break;
				} else printf("input error\n");
			}
		}
	} else printf("input error!\n");
}

void initConnection() {
	int result=;
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	memset(&servaddr,  0,  sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(DST_ADDR);
	servaddr.sin_port=htons(SERV_PORT);

	result=connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(result == -1) exit(0);
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

int segmentAnaly(char *recvline) {
	char *cityInput[MAX_INPUT];
	int i,k;
	if(recvline[0] == 0x01) return 1;
	else {
		for(i=2,k=0;recvline[i] != 0x00;i++,k++)
			cityInput[k]=recvline[i];
		cityInput[k]='\0';
		if(recvline[1] == 0x41) oneDay(cityInput,)
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	char cityInput[MAX_INPUT],queryInput[MAX_INPUT],segment[MAX_INPUT];
	initConnection();
	while(1) {
		//clear scream
		welcome();
		scanf("%s",cityInput);
		commandCheck(cityInput, 'a');
		if(realCity(cityInput)) {
			segmentConstruction(segment);
			send(sockfd, segment, SENT_LENGTH, 0);
			//clear scream
			query();
			while(1) {
				scanf("%s",queryInput);
				if(commandCheck(queryInput, 'b')) break;
				processQuery(cityInput, queryInput);
			}
		} else printf("Sorry, Server does not have weather information for city %s!\n", cityInput);
	}
	return 0;
}