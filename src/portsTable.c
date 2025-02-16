#include "portsTable.h"

/*  ports map "structure"
 *  *(map + port_number - 1) = true/false
 *  
 *  thanks of that can remember which port is used or not
 *  
 *  "- 1" because alocated memory starts with 0
 *  true -> port open
 *  false -> port closed  
 */

const int nports = NPORTS;

bool* new_map(){
    bool *ports_map = (bool*)malloc(nports * sizeof(bool));
    if(ports_map == NULL){
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < nports; i++){
        *(ports_map + i) = false;
    }

    return ports_map;
}

void change_port_state(bool **map, int port_number, bool status){
    *(*(map) + port_number -1) = status;
}