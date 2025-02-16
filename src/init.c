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

        /*  closing all open descriptors */
        if(resource_limit.rlim_max == RLIM_INFINITY){
            resource_limit.rlim_max = 1024;
        }
        for(int i = 0; i < resource_limit.rlim_max; i++){
            close(i);
        }

        /* descriptors 0,1,2 to /dev/null */
        int fd = open("/dev/null", O_RDWR);
        if(fd < 0)
            exit(EXIT_FAILURE);
        if(dup2(0, fd) < 0 || dup2(1, fd) < 0 || dup2(2, fd) < 0)
            exit(EXIT_FAILURE);
        
        close(fd);

        return process;
    }

    exit(EXIT_FAILURE);
}
