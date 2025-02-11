/*
 *  daemon initializing file 
 */
#include "daemonProcess.h"

/*
 *   change exit errors
 */

struct daemonProcess daemonInit(){
    deamon process;

    struct rlimit resource_limit;

    umask(0);

    /*   get maximum descriptors*/
    if(getrlimit(RLIMIT_NOFILE, &resource_limit) < 0){
        exit(EXIT_FAILURE);
    }

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

        return process;
    }
}
