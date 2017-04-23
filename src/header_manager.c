#include "header_manager.h" 


bool is_valid_protocol(char *ptcl){
	if( strcmp("HTTP/1.1", ptcl) != 0 && strcmp("HTTP/1.0", ptcl) != 0 ){
		return false;
	}else{
		return true;
	}
}

char* get_header(){
	char *header;

	char *status = "HTTP/1.1 200 OK\r\n";
	char *connection = "Connection: keep-alive\r\n";
	char *content_type = "Content-Type: text/html\r\n";
	char *server = "Server: " SERVER_NAME "\r\n\r\n"; // last space to let client know header is finished
	

	header = (char *) malloc(1 + strlen(connection)+ strlen(content_type) + strlen(server) + strlen(status) );
	strcpy(header, status);
        strcat(header, connection);
        strcat(header, content_type);
        strcat(header, server);

	return header;
}

