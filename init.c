/*
 * daemon initializing file 
 */
#include "daemonProcess.h"

struct daemonProcess daemonInit(){
    struct daemonProcess process;

    process.processPid = fork();

    if(process.processPid <= -1){
        /* fork error */
        fprintf(stderr, "error number 1: fork error");
        exit(1);
    }
    else if(process.processPid > 0){
        /*
         * parent process
         * have to kill it
         */
        
        printf("it's parent process\nchild process: %d\n", process.processPid);
        printf("parent process exiting with status 0\n");
        exit(0);

    }
    else if(process.processPid == 0){
        /*
         * child process
         * it going to be a daemon process
         */
        
        process.sid = setsid();
        if(process.sid < 0){
            /* setsid error */
            fprintf(stderr, "error number 2: sid error");
            exit(2);
        }
        
        umask(0);

        return process;
    }
}
