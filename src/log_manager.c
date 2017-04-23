#include "log_manager.h" 


void log_write_access_registry(char *ip, char *resource, char *status){
	FILE *file;
	file=fopen("../" LOG_FOLDER "access_log.txt", "a");

	if(file==NULL) {
		printf(ANSI_COLOR_RED "Error trying to write log file at ../" LOG_FOLDER "access_log.txt" ANSI_COLOR_RESET "\n");
	}
	else {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

		fprintf(file, " %d-%d-%d %d:%d:%d   |   %s   |   %s accessed file %s \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, status, ip, resource);
	}
	fclose(file);
}


void log_write_error_registry(char *message){
	FILE *file;
	file=fopen("../" LOG_FOLDER "error_log.txt", "a");

	if(file==NULL) {
		printf(ANSI_COLOR_RED "Error trying to write log file at ../" LOG_FOLDER "error_log.txt" ANSI_COLOR_RESET "\n");
	}
	else {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

		fprintf(file, " %d-%d-%d %d:%d:%d   |   %s\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, message);
	}
	fclose(file);
}
