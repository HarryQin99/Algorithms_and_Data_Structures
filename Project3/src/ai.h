#ifndef __AI__
#define __AI__

#include <stdint.h>
#include <unistd.h>
#include "utils.h"

#define STAGE_ONE 1
#define STAGE_TWO 2
#define STAGE_THREE 3
#define STAGE_FOUR 4


void initialize_ai();

void find_solution( state_t* init_state );
void free_memory(unsigned expanded_nodes);

node_t* create_init_node( state_t* init_state );


#endif
