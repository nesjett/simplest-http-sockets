#ifndef LOG_MANAGER_H_   /* Include guard */
#define LOG_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "colors.h"
#include "constants.h"

void log_write_access_registry(char *ip, char *file, int status);
void log_write_error_registry(char *message);
//char[32] get_timestamp();


#endif // LOG_MANAGER_H_
