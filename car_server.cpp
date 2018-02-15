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



const int  size = 2;


int joy[2] = {0,1};

char msg[256]="";

char buffer[256];


void decode() {

    int count = 0;

    snprintf(msg,sizeof(msg),"%s","");

    char *pch;

    pch = strtok(buffer,"RE");

    while (pch !=NULL) {

        joy[count] = atoi(pch);

        count++;

        pch = strtok(NULL,"R");

    }

}



void error(const char *msg)

{

    perror(msg);

    exit(1);

}

int sockfd, newsockfd, portno;

socklen_t clilen;

struct sockaddr_in serv_addr, cli_addr;

int n;

void server_setup() {
	
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) 

        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = 51717;

     serv_addr.sin_family = AF_INET;

     serv_addr.sin_addr.s_addr = INADDR_ANY;

     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,

              sizeof(serv_addr)) < 0) 

              error("ERROR on binding");

     listen(sockfd,5);

     clilen = sizeof(cli_addr);

     printf("Waiting for Client...\n");

     newsockfd = accept(sockfd, 

                 (struct sockaddr *) &cli_addr, 

                 &clilen);

     if (newsockfd < 0) 

          error("ERROR on accept");

     printf("Client Connected!!!\n");
	
}

int main(int argc, char *argv[]) {
	server_setup();
	int fd = serialOpen ("/dev/ttyUSB0, 115200) ;
	//int fd = serialOpen ("/dev/ttyUSB1", 115200) ;
    if (fd < 0){
        printf("error\n");
    }
		while (1) {
			bzero(buffer,256);
			n = read(newsockfd,buffer,255);
			//decode();
			if (n < 0) error("ERROR reading from socket");
			printf("Here is the message: %s\n",buffer);
			serialPuts(fd,buffer);
			n = write(newsockfd,"I got your message",18);
			if (n < 0) error("ERROR writing to socket");
		}
	close(newsockfd);
	close(sockfd);
	return 0; 

}
