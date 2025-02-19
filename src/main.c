#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include "daemonProcess.h"
#include "portsTable.h"

const int nports = 65535;
const __useconds_t refresh_time = 1 * 100000;

// To Do list
// - setting dynamic cheking of ports

bool port_check(int port_number){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0){
        syslog(LOG_ERR, "socket create error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port_number);

    errno = 0;
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    close(sock);
    if(errno == EADDRINUSE){
        return false;
    }
    else if(errno > 0 && errno != EADDRINUSE ){
        syslog(LOG_ERR, "unrecognized bind error, errno: %d", errno);
        exit(EXIT_FAILURE);
    }
    
    return true;
}

int main(int argc, char *argv[]){
    /*  initalizing a daemon process */
    daemon_ids process = daemonInit();
    syslog(LOG_INFO, "i'm alive with pid %d", process.processPid);

    bool *ports_map = new_map();
    int port_number = 0;

    while(1){
        for(port_number = 1; port_number < nports; port_number++){
            if(port_check(port_number)){
                /*  port is free */
                change_port_state(&ports_map, port_number, true);
            }
            else{
                /*  port is used */
                change_port_state(&ports_map, port_number, false);
                syslog(LOG_WARNING, "port %d is now open", port_number);
            }
            usleep(refresh_time);
        }
    }

    return 0;
}