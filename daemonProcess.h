#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#ifndef DAEMON_PROCESS_H
#define DAEMON_PROCESS_H

struct daemonProcess{
    int processPid;
    int sid;
};

struct daemonProcess daemonInit();

#endif