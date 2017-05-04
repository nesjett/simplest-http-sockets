#include "request_manager.h"


void processHTTP_REQUEST(int sd, struct sockaddr_in their_addr)
{
    	char buf[MAXDATASIZE];
   	char *comando, *resource, *protocol;
    	char archivo[256];
    	int fd = -1;
    	int bLeidos;

	int request_status = 0;
				
	if ((read(sd, buf, MAXDATASIZE)) == -1) {
		perror("recv--");
		return;
	}

	
	comando = strtok(buf, " ");
	resource = strtok(NULL, " ");
	protocol = strtok(NULL, "\r\n");


	// check if the protocol asked by client is valid on this server (HTTP/1.1 or HTTP/1.0)
	if( is_valid_protocol(protocol) == false ){
		request_status = 505; // HTTP version not supported

		if(p.DEBUG == 1){
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			printf(ANSI_COLOR_RED "[%d:%d:%d] Server: got connection for unsupported protocol from %s -> " ANSI_COLOR_BLUE "asking for %s" ANSI_COLOR_RESET "\n", tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(their_addr.sin_addr), resource);
		}
		
		log_write_error_registry("Unsupported protocol requested", &p);

		//exit(0);
	}

	
	if( is_valid_command(comando) == false && request_status == 0){
		request_status = 405; // Method not allowed


		if(p.DEBUG == 1){
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			printf(ANSI_COLOR_RED "[%d:%d:%d] Server: got connection for unsupported command from %s -> " ANSI_COLOR_BLUE "asking for %s" ANSI_COLOR_RESET "\n", tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(their_addr.sin_addr), resource);
		}
		
		log_write_error_registry("Unsupported command requested", &p);

		//exit(0);
	}
	
	

	if(request_status == 0){

		if( strcmp("", resource) == 0 || strcmp("/", resource) == 0 || strcmp(" ", resource) == 0 ){
			
			resource = strtok(p.DIRECTORY_INDEX, ",");
			if( resource != NULL ){
				// try to open the first index
				sprintf(archivo, "../%s/%s", p.DOCUMENT_ROOT, resource); // add another slash between /%s/s% because if url specifies a resource, it will be /file.html but if its empty, there is no slash
				fd = open(archivo, O_RDONLY);
		
				if(fd == -1)
					while( resource != NULL && fd == -1 ){
						resource = strtok(NULL, ",");
						sprintf(archivo, "../%s/%s", p.DOCUMENT_ROOT, resource); // add another slash between /%s/s% because if url specifies a resource, it will be /file.html but if its empty, there is no slash
						fd = open(archivo, O_RDONLY);
					}
			}

			
		}else{
			sprintf(archivo, "../%s%s", p.DOCUMENT_ROOT, resource); // add a ".." for security reasons (prevent people from accessing system folders)
			//procesar archivo
			fd = open(archivo, O_RDONLY);
		}

		//procesar archivo
		//fd = open(archivo, O_RDONLY);

		if(fd==-1)
		{		
			if(errno == 2) //no such file or directory
				request_status = 404; // FILE NOT FOUND 404
			if(errno == 13) // permision denied
				request_status = 403; // FORBRIDDEN 403


			if(p.DEBUG == 1){
				// file not found
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				printf(ANSI_COLOR_GREEN "[%d:%d:%d] Server: got connection from %s -> " ANSI_COLOR_YELLOW "file not found %s" ANSI_COLOR_RESET "\n", tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(their_addr.sin_addr), archivo);
			}

		}else{
			request_status = 200; // 200 OK


			if(p.DEBUG == 1){
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				printf(ANSI_COLOR_GREEN "[%d:%d:%d] Server: got connection from %s -> " ANSI_COLOR_BLUE "serving %s" ANSI_COLOR_RESET "\n", tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(their_addr.sin_addr), archivo);
			}
		}
	}


	// PROCESS HEADER & BODY
	char *header = get_header(resource, request_status);
	sprintf(buf, "%s", header);
	free(header); // free the memory allocated for the header string
	write(sd, buf, strlen(buf));

	if(fd != -1 && request_status == 200){
		while (bLeidos=read(fd, buf, sizeof(buf))>0){
			write(sd, buf, strlen(buf));
		}

		close(fd);
	}else{
		// get body for error message


		//procesar archivo de error
		sprintf(archivo, "../%s%d.html", DEFAULT_ERROR_RESPONSES_FOLDER, request_status);
		fd = open(archivo, O_RDONLY);
	
		if(fd==-1){
			strcpy(buf , "<hrml><head></head><body>Error file not found, please, do not delete /default_responses/ folder nor its content</body></html>");
			write(sd, buf, strlen(buf));
		}else{
			while (bLeidos=read(fd, buf, sizeof(buf))>0){
				write(sd, buf, strlen(buf));
			}

			close(fd);
		}
		
	}


	// log the connection to the server
	log_write_access_registry(inet_ntoa(their_addr.sin_addr), resource, request_status, &p); // TODO: Use the right status code, not just 200
}

