#include <stdbool.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <unistd.h>

#ifndef PORTS_TABLE_H
#define PORTS_TABLE_H

bool* new_map(void);
void change_port_state(bool**, int, bool);
bool port_check(int);

#endif

//#define NPORTS 65535 /* 2^16