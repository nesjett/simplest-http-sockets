# Very simple HTTP server & client
This project is intended as an example for those who want to learn how HTTP protocol works in both, client and server software, from the very basics to a more advanced handling.  
---
**AUTHOR WEBSITE**

You can find more about the author, this and other of his projects at [Nestor Sabater's Portfolio](https://nsabater.com/a-simple-http-server-client-for-begginers)

---

  
It's developed in C, keeping in mind the readability as priority.  
  
The project is not production ready and can be improved in many ways, from better encapsulation to better security algorithms, but as mentioned, It aims to provide a starting point for those willing to learn.  

> This repository IS NOT using any 3rd party libraries, everything is made simple enought to work and be understandable
  
  
![Image of Server Running](https://nsabater.com/wp-content/uploads/2020/04/Screenshot_172.png)
  
  
## Features

### Easy server configuration
Use of a configuration file
![Server configuration](https://nsabater.com/wp-content/uploads/2020/04/Screenshot_169.png)
  
  
### Realtime records
Colored connection records for testing and debugging
![Colore real time console](https://nsabater.com/wp-content/uploads/2020/04/Screenshot_170.png)

### Logs
Two log files to record all server requests and errors
![Access log](https://nsabater.com/wp-content/uploads/2020/04/Screenshot_173.png)
![Error log](https://nsabater.com/wp-content/uploads/2020/04/Screenshot_174.png)


## Project structure
- server/**bin**
  - Contains all executables for <ins>server</ins> and for <ins>client</ins>
- server/**config**
  - Contains configuration files for server. This files are used to configure different parameters in the server.
- server/**default_responses**
  - Contains the default html response pages, if not provided in the website we want to access.(500, 404, ...) 
- server/**public_html**
  - Contains the publicly accesible site files for the server. Ex: index.html, myWebsite.html, etc.
- server/**logs**
  - Contains the log files for access and errors.
- **src**
  - Contains all .c y .h files, to get a cleaner code but keeping it readable for begginers.


  
## How to use

To **compile**: gcc -o ../server/bin/mi_http server.c config_manager.c colors.h constants.h log_manager.c header_manager.c   
To **execute client**: ./client [ip/host] [port] [file]   
To **execute server**: ./server  


