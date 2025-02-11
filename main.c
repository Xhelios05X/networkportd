#include <stdio.h>
#include <stdlib.h>
#include "daemonProcess.h"

// To Do list
// - writing outputs to log file
// - cheking ports
// - header file with port acvivity structure
// - dynamic buffer between ports and log file
// - setting dynamic cheking of ports

/*
 * main function of daemon
 */
int main(int argc, char *argv[]){
    /* initalizing a daemon process */
    struct daemonProcess process = daemonInit();
    if(process.error == 1){
        fprintf(stderr, "error number 3: child process initial error");
        exit(3);
    }
    printf("child process has now his own group %d\n", process.sid);


    return 0;
}