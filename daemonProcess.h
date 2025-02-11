#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/resource.h>

#ifndef DAEMON_PROCESS_H
#define DAEMON_PROCESS_H

typedef struct daemonProcess{
    int processPid;
    int sid;
} deamon;

struct daemonProcess daemonInit();

#endif