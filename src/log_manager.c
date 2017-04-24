#include "log_manager.h" 


void log_write_access_registry(char *ip, char *resource, int status){
	FILE *file;
	file=fopen("../" LOG_FOLDER "access_log.txt", "a");

	if(file==NULL) {
		printf(ANSI_COLOR_RED "Error trying to write log file at ../" LOG_FOLDER "access_log.txt" ANSI_COLOR_RESET "\n");
	}
	else {
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);

		fprintf(file, " %d-%d-%d %d:%d:%d   |   %d   |   %s accessed file %s \n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, status, ip, resource);
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

/*
void printf_timed(char* color, char* text){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	printf("%s [%d:%d:%d] Server: got connection from %s -> " ANSI_COLOR_YELLOW "file not found %s" ANSI_COLOR_RESET "\n", color, tm.tm_hour, tm.tm_min, tm.tm_sec, inet_ntoa(their_addr.sin_addr), archivo);
}*/
/*
char[32] get_timestamp(){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char tmp_time[32];
	sprintf(tmp_time, "[%d:%d:%d]", tm.tm_hour, tm.tm_min, tm.tm_sec);
	return tmp_time;
}*/
