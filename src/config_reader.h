#ifndef CONFIG_READER_H_   /* Include guard */
#define CONFIG_READER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "colors.h"

int foo(int x);  /* An example function declaration */

struct params {
	int LISTEN_PORT, MAX_CLIENTS, DEBUG;
	char *DIRECTORY_INDEX, *SECURITY_FILE, *DOCUMENT_ROOT;
};

struct params read_config();

void print_config_params(struct params p);

#endif // CONFIG_READER_H_
