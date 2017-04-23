#include "config_manager.h"  /* Include the header (not strictly necessary here) */

struct params read_config(char file[256]) {
	struct params t = {-1,-1,-1,NULL,NULL,NULL}; // Init struct for later check for defaults
	char buf[512];
	char *command;
	FILE *fd;

	fd = fopen(file, "r"); // open file
	
	while (fgets(buf, sizeof buf, fd) != NULL) {
	    // process line here
		command = strtok(buf, " ");
		if(command != NULL && strcmp("#", command) != 0){

			// INT PARAMS
			if( strcmp("DEBUG", command) == 0 ){
				t.DEBUG = atoi(strtok(NULL, " "));
				continue;
			}


			if( strcmp("LISTEN_PORT", command) == 0 ){
				t.LISTEN_PORT = atoi(strtok(NULL, " "));
				continue;
			}

			if( strcmp("MAX_CLIENTS", command) == 0 ){
				t.MAX_CLIENTS = atoi(strtok(NULL, " "));
				continue;
			}


			// STRING PARAMS
			if( strcmp("DIRECTORY_INDEX", command) == 0 ){
				t.DIRECTORY_INDEX = strtok(NULL, " ");
				// TODO: the next printf works here, but not in the print_config_params(), which shows unespected string
				//printf("DIRECTORY_INDEX: %s\n", t.DIRECTORY_INDEX);
				continue;
			}

			if( strcmp("SECURITY_FILE", command) == 0 ){
				t.SECURITY_FILE = strtok(NULL, " ");
				continue;
			}

			if( strcmp("DOCUMENT_ROOT", command) == 0 ){
				t.DOCUMENT_ROOT = strtok(NULL, " ");
				continue;
			}


		}
	}

	fclose(fd); // close file

	t = check_for_defaults(t); // check struct to fill with default values the params that were not present on the config file

	if(t.DEBUG == 1)
		print_config_params(t);

	return t;
}

struct params check_for_defaults(struct params p){
	if(p.DEBUG == -1)
		p.DEBUG = DEFAULT_DEBUG;
	if(p.LISTEN_PORT == -1)
		p.LISTEN_PORT = DEFAULT_LISTEN_PORT;
	if(p.MAX_CLIENTS == -1)
		p.MAX_CLIENTS = DEFAULT_MAX_CLIENTS;
	if(p.DIRECTORY_INDEX == NULL)
		p.DIRECTORY_INDEX = DEFAULT_DIRECTORY_INDEX;
	if(p.SECURITY_FILE == NULL)
		p.SECURITY_FILE = DEFAULT_SECURITY_FILE;
	if(p.DOCUMENT_ROOT == NULL)
		p.DOCUMENT_ROOT = DEFAULT_DOCUMENT_ROOT;

	return p;
}

void print_config_params(struct params p){
	printf(ANSI_COLOR_MAGENTA "Server configuration:\n-----------------------------------------\n\n");

	if(p.DEBUG == 1)
		printf("DEBUG:" ANSI_COLOR_CYAN " True\n" ANSI_COLOR_MAGENTA);
	else
		printf("DEBUG:" ANSI_COLOR_CYAN " False\n" ANSI_COLOR_MAGENTA);
	printf("LISTEN_PORT:" ANSI_COLOR_CYAN " %d\n" ANSI_COLOR_MAGENTA, p.LISTEN_PORT);
	printf("MAX_CLIENTS:" ANSI_COLOR_CYAN " %d\n" ANSI_COLOR_MAGENTA, p.MAX_CLIENTS);
	printf("DIRECTORY_INDEX:" ANSI_COLOR_CYAN " %s\n" ANSI_COLOR_MAGENTA, p.DIRECTORY_INDEX);
	printf("SECURITY_FILE:" ANSI_COLOR_CYAN " %s\n" ANSI_COLOR_MAGENTA, p.SECURITY_FILE);
	printf("DOCUMENT_ROOT:" ANSI_COLOR_CYAN " %s\n" ANSI_COLOR_MAGENTA, p.DOCUMENT_ROOT);

	printf("\n-----------------------------------------" ANSI_COLOR_RESET "\n\n\n");
}
















