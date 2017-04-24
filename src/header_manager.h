#ifndef HEADER_MANAGER_H_   /* Include guard */
#define HEADER_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "constants.h"


bool check_protocol(char *ptcl);
char* get_header();
char* get_content_type(char *extension);
char* get_status_code(int status);

#endif // HEADER_MANAGER_H_
