/*
 ** client.c -- Ejemplo de cliente de sockets de flujo
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

//CUSTOM
#include "colors.h"


#define MAXDATASIZE 16384 

// ./cliente cliente hostname puerto recurso

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    char miRequest[256];
    char buf[MAXDATASIZE];
    char *comando, *resource, *protocol;
    struct hostent *he;
    struct sockaddr_in their_addr; // información de la dirección de destino
    
    if (argc != 5) {
        fprintf(stderr,"usage: [hostname] [puerto] [recurso] [comando]\n");
        exit(1);
    }

    if ((he=gethostbyname(argv[1])) == NULL) {  // obtener información de máquina
        perror("gethostbyname--");
        exit(1);
    }
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    
    their_addr.sin_family = AF_INET;    // Ordenación de bytes de la máquina
    their_addr.sin_port = htons(atoi(argv[2]));  // short, Ordenación de bytes de la red  //atoi funcion
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(their_addr.sin_zero), '0', 8);  // poner a cero el resto de la estructura
    
    if (connect(sockfd, (struct sockaddr *)&their_addr,
                sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }
    printf("%s",argv[4]);
    // REQUEST
    if(strcmp("GET", argv[4]) == 0){//PASAR A CHAR
    	sprintf(miRequest, "GET %s HTTP/1.0\r\n\r\n", argv[3]);
	//strcpy(miRequest, "GET %s HTTP/1.0\r\n\r\n");
     }else{
	    if(strcmp("HEAD", argv[4]) == 0){//PASAR A CHAR
	    	sprintf(miRequest, "HEAD %s HTTP/1.0\r\n\r\n", argv[3]);
		//strcpy(miRequest, "HEAD %s HTTP/1.0\r\n\r\n");
	     }else{
		    if(strcmp("DELETE", argv[4]) == 0){//PASAR A CHAR
		    	sprintf(miRequest, "DELETE %s HTTP/1.0\r\n\r\n", argv[3]);
			//strcpy(miRequest, "DELETE %s HTTP/1.0\r\n\r\n");
		     }else{
			perror("NOT VALID COMMAND");
        		exit(0);
			}
		}
	}

    //sprintf(miRequest, "GET %s HTTP/1.0\r\n\r\n", argv[3]);
 	

    time_t tiempo = time(0);//--HORA--
        struct tm *tlocal = localtime(&tiempo);
        char output[128];
        strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);

    if (send(sockfd, miRequest, strlen(miRequest), 0) == -1)
        perror("send");

    if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    //lenght
    buf[numbytes] = '\0';

	    

    printf(ANSI_COLOR_BLUE "Connection: " ANSI_COLOR_RESET "keep-alive\r\n");
    printf(ANSI_COLOR_BLUE "Content-lenght: " ANSI_COLOR_RESET "%d\r\n",numbytes);
    printf(ANSI_COLOR_BLUE "Date: " ANSI_COLOR_RESET"%s\r\n",output);
    printf(ANSI_COLOR_BLUE "Received: "ANSI_COLOR_RESET"%s",buf);
    //printf("Server: %s",buf);
   /* char content_type[128];
	sprintf(content_type, "Content-type: %s\r\n", get_content_type(resource));*/


   
    //printf("Connection: keep-alive\r\n")
    //printf("Content lenght: %s\r\n",largo);
    //printf("Date: %s\r\n",fecha);

    
    close(sockfd);
    
    return 0;
}
