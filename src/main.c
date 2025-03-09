#include "daemonProcess.h"
#include "portsTable.h"

const nports_t nports = 65535;
const __useconds_t refresh_time = 10000;

// To Do list
// - add config file
// - dynamic wating for a singal with a thread
// - setting dynamic cheking of ports

int main(int argc, char *argv[]){
    /*  initalizing a daemon process */
    daemon_ids process = daemonInit();
    syslog(LOG_INFO, "i'm alive with pid %d", process.processPid);

    bool *ports_map = new_map();
    int port_number = 0;
    bool state = false;

    while(1){
        for(port_number = 1; port_number < nports; port_number++){
            state = port_check(port_number);

            if(state != (*(ports_map + port_number - 1))){
                /*  port changed state */
                change_port_state(&ports_map, port_number, state);

                if(state){
                    /*  port is now open */
                    syslog(LOG_WARNING, "port %d now is open", port_number);
                }
                else{
                    /*  port is now closed */
                    syslog(LOG_INFO, "port %d is now closed", port_number);
                }
            }
            usleep(refresh_time);
        }
    }

    exit(EXIT_SUCCESS);
}