#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <time.h>
#include <wiringSerial.h>

using namespace std;

const int  size = 2;

int joy[2] = {0,1};

char msg[256]="";
char buffer[256];

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

void encode(){
	int i =0;
    for (i=0; i<size; i++) {
        snprintf(msg,sizeof(msg),"%d",joy[i]);
        strcat(buffer,msg);
        strcat(buffer,"R");

    }
}



void error(const char *msg) {
    perror(msg);
    exit(0);
}

int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;

void client_setup() {
	portno = 51717;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0) {
		error("ERROR opening socket\n");
	}
	//server = gethostbyname("car_client");
	server = gethostbyname("localhost");
	
	bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, 

         (char *)&serv_addr.sin_addr.s_addr,

         server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 

        error("ERROR connecting");
}


int main(int argc, char *argv[]) {
	int fd = serialOpen ("/dev/ttyACM0", 115200) ;
    if (fd < 0){
        printf("error\n");
    }
	client_setup();
    while (1) {
		bzero(buffer,256);
		//encode();
		serialGetString(fd,size,buffer);
		printf("Sending Message: %s\n",buffer);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) {
			 error("ERROR writing to socket");
		}
		bzero(buffer,256);

		n = read(sockfd,buffer,255);

		if (n < 0) {
			 error("ERROR reading from socket");
		}
		printf("%s\n",buffer);

		sleep(1);

    }
	serialClose (fd) ;
    close(sockfd);
    return 0;

}
