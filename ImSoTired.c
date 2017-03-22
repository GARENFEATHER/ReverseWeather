#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_INPUT 1024

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

int main(int argc, char const *argv[])
{
	char cityInput[MAX_INPUT],queryInput[MAX_INPUT];
	while(1) {
		//clear scream
		welcome();
		scanf("%s",cityInput);
		commandCheck(cityInput, 'a');
		if(realCity(cityInput)) {
			//send
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