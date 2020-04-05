# Very simple HTTP server & client
This project is intended as an example for those who want to learn how HTTP protocol works, from the very basics to a more advanced handling.  
  
It's developed in C, keeping in mind the readability as priority.  
  
The project is not production ready and can be improved in many ways, from better encapsulation to better security algorithms, but as mentioned, It aims to provide a starting point for those willing to learn.  
  
  
## How to use

To compile: gcc -o ../server/bin/mi_http server.c config_manager.c colors.h constants.h log_manager.c header_manager.c   
To execute client: ./client [ip/host] [port] [file]   
To execute server: ./server  
