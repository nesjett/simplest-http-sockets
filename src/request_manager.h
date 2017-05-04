#ifndef REQUEST_MANAGER_H_   /* Include guard */
#define REQUEST_MANAGER_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

// CUSTOM INCLUDES
#include "colors.h"
#include "constants.h"
#include "config_manager.h"
#include "log_manager.h"
#include "header_manager.h"
#include "request_manager.h"

void processHTTP_REQUEST(int sd, struct sockaddr_in their_addr);

#endif // REQUEST_MANAGER_H_
