#include <sys/socket.h>
#include <arpa/inet.h>
#include "portsTable.h"

/*  ports map "structure"
 *  *(map + port_number - 1) = true/false
 *  
 *  thanks of that can remember which port is used or not
 *  
 *  "- 1" because alocated memory starts with 0
 *  true -> port open
 *  false -> port closed  
 */

bool port_check(int port_number){
    /*  function checks if port is open:
     *  true - open
     *  false - close
     */
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
    if(close(sock) < 0){
        syslog(LOG_ERR, "close error");
    }

    if(errno == EADDRINUSE){
        return true;
    }
    else if(errno > 0 && errno != EADDRINUSE ){
        syslog(LOG_ERR, "unrecognized bind error, errno: %d", errno);
        exit(EXIT_FAILURE);
    }
    
    return false;
}

bool* new_map(void){
    const int nports = 65535;

    bool *ports_map = (bool*)malloc(nports * sizeof(bool));
    if(ports_map == NULL){
        syslog(LOG_ERR, "malloc error");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < nports; i++){
        *(ports_map + i) = false;
    }

    return ports_map;
}

void change_port_state(bool **map, int port_number, bool status){
    /* function chagnes port state */
    *(*(map) + port_number - 1) = status;
}