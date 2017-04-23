/*
 ** server.c -- Ejemplo de servidor de sockets de flujo
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

// CUSTOM INCLUDES
#include "colors.h"
#include "config_reader.h"
#define CONFIG_FILE "../config/server_config.conf"


#define MYPORT 3490    // Puerto al que conectarán los usuarios

#define BACKLOG 10     // Cuántas conexiones pendientes se mantienen en cola

#define MAXDATASIZE 16384 // máximo número de bytes que se pueden leer de una vez

struct params p;

void sigchld_handler(int s)
{
    while(wait(NULL) > 0);
}

void tratarHTTP_REQUEST(int sd)
{
    	char buf[MAXDATASIZE];
   	char *comando, *recurso, *protocolo;
    	char archivo[256];
    	int fd;
    	int bLeidos;
				
	if ((read(sd, buf, MAXDATASIZE)) == -1) {
		perror("recv--");
		return;
	}

	
	comando = strtok(buf, " ");
	recurso = strtok(NULL, " ");
	protocolo = strtok(NULL, "\r\n");

	sprintf(archivo, ".%s", recurso); // seguridad, directorio relativo
		/*
				printf(" %s\n", strtok(buf, " "));
				if( strcmp("GET", strtok(buf, " ")) != 0 ){
				perror("no GET request found");
						exit(1);
				}

	
		*/
				//procesar archivo
	fd = open(archivo, O_RDONLY);
/*
				if(fp==NULL)
				{
					printf("Some problem in opening the file"); // file not found
					exit(0);
				} 
*/

	
	
	if(p.DEBUG == 1){
		printf(ANSI_COLOR_BLUE "Serving file %s" ANSI_COLOR_RESET "\n", archivo);
		
		sprintf(buf, "%s \n", archivo); // DEBUG
		write(sd, buf, strlen(buf)); // DEBUG
	}


	sprintf(buf, "HTTP/1.1 200 OK\r\n\r\n");
	write(sd, buf, strlen(buf));

	while (bLeidos=read(fd, buf, sizeof(buf))>0){
		write(sd, buf, strlen(buf));
	}


	close(fd);
}
			


int main(void)
{
    int sockfd, new_fd;  // Escuchar sobre sock_fd, nuevas conexiones sobre new_fd
    struct sockaddr_in my_addr;    // información sobre mi dirección
    struct sockaddr_in their_addr; // información sobre la dirección del cliente
    int sin_size;
    struct sigaction sa;
    int yes=1;

// init server config
	
	p = read_config(CONFIG_FILE);

        
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    
    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    
    my_addr.sin_family = AF_INET;         // Ordenación de bytes de la máquina
    my_addr.sin_port = htons(MYPORT);     // short, Ordenación de bytes de la red
    my_addr.sin_addr.s_addr = INADDR_ANY; // Rellenar con mi dirección IP
    memset(&(my_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura
    
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))
        == -1) {
        perror("bind");
        exit(1);
    }
    
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
    
    sa.sa_handler = sigchld_handler; // Eliminar procesos muertos
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }
    
    while(1) {  // main accept() loop
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, (socklen_t*)&sin_size)) == -1) {
            perror("accept");
            continue;
        }else{
		if(p.DEBUG == 1)
			printf(ANSI_COLOR_GREEN "Server: got connection from %s" ANSI_COLOR_RESET "\n", inet_ntoa(their_addr.sin_addr)
			);

		if (!fork()) { // Este es el proceso hijo
			close(sockfd); // El hijo no necesita este descriptor
			tratarHTTP_REQUEST(new_fd);				
			close(new_fd);
			exit(0);
		}
		
        }
        close(new_fd);  // El proceso padre no lo necesita
    }
    
    return 0;
}
