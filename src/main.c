#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdbool.h>
#include "daemonProcess.h"
#include "portsTable.h"

const int nports = NPORTS;

// To Do list
// - writing outputs to log file
// - header file with port acvivity structure
// - setting dynamic cheking of ports

bool port_check(int port_number){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_number);

    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0){
        if(errno == EADDRINUSE){
            close(sock);
            return false;
        }
        else{
            close(sock);
            exit(EXIT_FAILURE);
        }
    }
    close(sock);
    return true;
}

int main(int argc, char *argv[]){
    /*  initalizing a daemon process */
    struct daemonProcess process = daemonInit();
    
    printf("child process has now his own group %d\n", process.sid);

    for(int port_number = 1; port_number < nports; port_number++){
        if(port_check(port_number)){
            /*  port is free */
        }
        else{
            /*  port is used */
        }
    }

    return 0;
}