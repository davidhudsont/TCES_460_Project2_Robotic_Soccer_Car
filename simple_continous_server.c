/* A simple server in the internet domain using TCP

   The port number is passed as an argument */

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/types.h> 

#include <sys/socket.h>

#include <netinet/in.h>



#define size 5

char msg[256]="";

char buffer[256];


void decode() {

    int count = 0;

    snprintf(msg,sizeof(msg),"%s","");

    char *pch;

    pch = strtok(buffer,"RE");

    while (pch !=NULL) {

        rbtfingers[count] = atoi(pch);

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

int main(int argc, char *argv[])

{

	server_setup();
     while (1) {

		 bzero(buffer,256);

		 n = read(newsockfd,buffer,255);

		 if (n < 0) error("ERROR reading from socket");

		 printf("Here is the message: %s\n",buffer);

		 decode();

		 int i =0;

		 for (i=0; i<size; i++) {

			printf("%d\n",rbtfingers[i]);

		 }

		 n = write(newsockfd,"I got your message",18);

		 if (n < 0) error("ERROR writing to socket");

		 sleep(1);

     }

     close(newsockfd);

     close(sockfd);

     return 0; 

}