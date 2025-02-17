/*
 *  daemon initializing file 
 */
#include "daemonProcess.h"

daemon_ids daemonInit(void){
    daemon_ids process;
    struct rlimit resource_limit;
    openlog("portsDaemon", LOG_PID, LOG_DAEMON);

    umask(0);

    /*   get maximum descriptors*/
    if(getrlimit(RLIMIT_NOFILE, &resource_limit) < 0){
        syslog(LOG_ERR, "can't get maximum number of descriptors");
        exit(EXIT_FAILURE);
    }

    int pid = fork();
    if(pid <= -1){
        /* fork error */
        syslog(LOG_ERR, "fork error");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0){
        /*
         * parent process
         * have to kill it
         */
        
        printf("it's parent process\nchild process: %d\n", pid);
        printf("parent process exiting with status 0\n");
        exit(EXIT_SUCCESS);

    }
    else if(pid == 0){
        /*
         * child process
         * it going to be a daemon process
         */
        if(chdir("/") < 0){
            syslog(LOG_ERR, "chdir error");
            exit(EXIT_FAILURE);
        }
        
        int sid = setsid();
        if(sid < 0){
            /* setsid error */
            syslog(LOG_ERR, "sid error");
            exit(EXIT_FAILURE);
        }
        syslog(LOG_INFO, "i have sid");

        /*  closing all open descriptors */
        if(resource_limit.rlim_max == RLIM_INFINITY){
            resource_limit.rlim_max = 1024;
        }
        for(int i = 0; i < resource_limit.rlim_max; i++){
            close(i);
        }
        syslog(LOG_INFO, "my descriptors are closed");


        /* descriptors 0,1,2 to /dev/null */
        int fd = open("/dev/null", O_RDWR);
        if(fd < 0){
            syslog(LOG_ERR, "can't open /dev/null");
            exit(EXIT_FAILURE);
        }
        if(dup2(fd, STDERR_FILENO) < 0 || dup2(fd, STDIN_FILENO) < 0 || dup2(fd, STDOUT_FILENO) < 0){
            syslog(LOG_ERR, "can't duplcate /dev/null descriptor");
            exit(EXIT_FAILURE);
        }

       process.processPid = getpid();
       process.sid = sid;
       return process;
    }
}
