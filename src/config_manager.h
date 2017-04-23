#ifndef CONFIG_MANAGER_H_   /* Include guard */
#define CONFIG_MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "colors.h"
#include "constants.h"

struct params {
	int LISTEN_PORT, MAX_CLIENTS, DEBUG;
	char *DIRECTORY_INDEX, *SECURITY_FILE;
	char *DOCUMENT_ROOT;
};

struct params read_config();


struct params check_for_defaults(struct params p);
void print_config_params(struct params p);

#endif // CONFIG_MANAGER_H_
