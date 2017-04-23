#ifndef CONSTANTS_H_   /* Include guard */
#define CONSTANTS_H_


#define DEFAULT_LISTEN_PORT 8880
#define DEFAULT_MAX_CLIENTS 10
#define DEFAULT_DEBUG 1

#define DEFAULT_DIRECTORY_INDEX "index.html,index.htm,index.txt";
#define DEFAULT_SECURITY_FILE ".htaccess";
#define DEFAULT_DOCUMENT_ROOT "public_html";
/*
static const int DEFAULT_LISTEN_PORT = 8880;
static const int DEFAULT_MAX_CLIENTS = 10;
static const int DEFAULT_DEBUG = 1;
*/

#define CONFIG_FILE "../config/server_config.conf"
#define MAXDATASIZE 16384 // max number of bytes the buffer can read at once

#endif // CONSTANTS_H_
