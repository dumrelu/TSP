#include "common.h"
#include "search.h"

int main(int argc, char ** argv) {
	int world_size, world_rank;
	common_mpi_init(&world_size, &world_rank);

	if(world_rank == MASTER)
		master_run(argc, argv, world_size, world_rank);
	else
		slave_run(world_size, world_rank);

	common_mpi_end(OK);
}
