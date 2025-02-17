#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <syslog.h>

#ifndef DAEMON_PROCESS_H
#define DAEMON_PROCESS_H

typedef struct daemonProcess{
    int processPid;
    int sid;
} daemon_ids;

daemon_ids daemonInit();

#endif