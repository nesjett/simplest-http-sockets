#include "header_manager.h" 


bool is_valid_protocol(char *ptcl){
	if( strcmp("HTTP/1.1", ptcl) != 0 && strcmp("HTTP/1.0", ptcl) != 0 ){
		return false;
	}else{
		return true;
	}
}

bool is_valid_command(char *cmd){
	if( strcmp("GET", cmd) != 0 && strcmp("PUT", cmd) != 0 && strcmp("DELETE", cmd) != 0 && strcmp("HEADE", cmd) != 0 ){
		return false;
	}else{
		return true;
	}
}

char* get_header(char* resource, int status){
	char *header;

	char protocol[256];
	sprintf(protocol, "HTTP/1.1 %s\r\n", get_status_code(status));

	char *connection = "Connection: keep-alive\r\n";

	char content_type[128];
	sprintf(content_type, "Content-type: %s\r\n", get_content_type(resource));


	char *server = "Server: " SERVER_NAME "\r\n\r\n"; // last space to let client know header is finished
	

	header = (char *) malloc(1 + strlen(connection)+ strlen(content_type) + strlen(server) + strlen(protocol) );
	strcpy(header, protocol);
        strcat(header, connection);
        strcat(header, content_type);
        strcat(header, server);

	return header;
}


char* get_content_type(char *resource){
	if( strstr(resource, ".js") != NULL )
		return "application/javascript";
	if( strstr(resource, ".json") != NULL )
		return "application/json";
	if( strstr(resource, ".html") != NULL )
		return "text/html";
	if( strstr(resource, ".css") != NULL )
		return "text/css";
	if( strstr(resource, ".txt") != NULL )
		return "text/plain";
	if( strstr(resource, ".png") != NULL )
		return "image/png";
	if( strstr(resource, ".jpg") != NULL )
		return "image/jpg";
	if( strstr(resource, ".gif") != NULL )
		return "image/gif";

	return "text/html"; // default value
}

char* get_status_code(int status){
	if(status == 200)	
		return "200 OK";
	if(status == 301)	
		return "301 Moved Permanently";
	if(status == 400)	
		return "400 Bad Request";
	if(status == 403)	
		return "403 Forbidden";
	if(status == 404)	
		return "404 Not Found";
	if(status == 405)	
		return "405 Method Not Allowed";
	if(status == 500)	
		return "500 Internal Server Error";
	if(status == 503)	
		return "503 Service Unavailable";
	if(status == 505)	
		return "505 HTTP Version Not Supported";

	return "500 Internal Server Error"; // default value
}








