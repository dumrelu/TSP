#ifndef MASTER_H
#define MASTER_H

#include "common.h"

void master_run(
	int argc, 
	char ** argv, 
	int world_size, 
	int world_rank
);

void master_send_file(
	const char * filename, 
	int world_size
);

void master_search(
	char * keyword,
	int world_size
);


#endif /*MASTER_H*/
