#include <stdbool.h>
#include <stdlib.h>
#include <syslog.h>

#ifndef PORTS_TABLE_H
#define PORTS_TABLE_H

bool* new_map(void);
void change_port_state(bool **map, int port_number, bool status);

#endif

//#define NPORTS 65535 /* 2^16