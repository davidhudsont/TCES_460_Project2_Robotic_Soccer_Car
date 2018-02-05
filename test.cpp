#include <iostream>
#include <time.h>
#include <unistd.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <string.h>

using namespace std;

void serialGetString(int fd, int size,char * buffer){
    memset(buffer,0,sizeof(buffer));
    for(int i = 0; i < size ;i++){
	char tmp = serialGetchar(fd);
	if (tmp == '\n') {
		return;
	}
        buffer[i] = tmp;
    }
}

int size = 20;
char buffer[20];

int  main(void)
{
    int fd = serialOpen ("/dev/ttyACM0", 115200) ;
    if (fd < 0){
        printf("error\n");
    }
    //char buffer[6];
    while(1){
        char temp;
        //temp = serialGetchar(fd);
        serialGetString(fd,size,buffer);
        //printf("%c\n",temp);
        printf("%s\n",buffer);
    }
    serialClose (fd) ;
    return 0;
}
