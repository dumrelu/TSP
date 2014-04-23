#include "common.h"

int common_send_int(int send, MessageType type, int destination) {
	MPI_Send(&send, 1, MPI_INT, destination, type, MPI_COMM_WORLD);
	return 1;
}

int common_send_char(char * send, MessageType type, int destination) {
	MPI_Send(send, BUFFER_SIZE, MPI_CHAR, destination, type, MPI_COMM_WORLD);
	return 1;
}

int common_recv_int(MessageType * type) {
	int recv;
	MPI_Status status;

	MPI_Recv(&recv, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	*type = status.MPI_TAG;

	return recv;
}

char * common_recv_char(MessageType * type) {
	MPI_Status status;
	char * recv = (char *) malloc( BUFFER_SIZE * sizeof(char) );

	MPI_Recv(recv, BUFFER_SIZE, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	
	*type = status.MPI_TAG;

	return recv;
}

int common_reduce(int * send, int * recv, MPI_Op op) {
	int dummy = 0;	

	if(!send) {
	//If master
		MPI_Reduce(&dummy, recv, 1, MPI_INT, op, MASTER, MPI_COMM_WORLD);
		return 1;
	} else if(!recv) {
		MPI_Reduce(send, &dummy, 1, MPI_INT, op, MASTER, MPI_COMM_WORLD);
		return 1;
	} else
		return 0;
}

void common_mpi_init(int * world_size, int * world_rank) {
	//Initializare
  	MPI_Init(NULL, NULL);
  
  	//Obtine numarul de procesoare
  	MPI_Comm_size(MPI_COMM_WORLD, world_size);
  
  	//Rang procesor
  	MPI_Comm_rank(MPI_COMM_WORLD, world_rank);
}

void common_mpi_end(ExitType type) {
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	MPI_Finalize();

	printf("Process %d ended ", world_rank);
	switch(type) {
		case OK:
			printf("as excepted.\n");
			break;
		case FILE_ERROR:
			printf("in a file error.\n");
			break;
		default:
			printf("with and unknown error.\n");
			break;
	}

	exit(type);
}
