#ifndef SLAVE_H
#define SLAVE_H

#include "common.h"
#include "search.h"

void slave_run(
	int world_size, 
	int world_rank
);

void slave_add_line(
	SearchNode ** root,
	char * line, 
	int row
);

void slave_search(
	SearchNode * root, 
	const char * keyword
);


#endif /*SLAVE_H*/
