#ifndef COMMON_H
#define COMMON_H

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MASTER 0

typedef enum {
	ADD_LINE /*Indicates that the next message contains a line of text*/, 
	ADD_WORD /*Indicates that the next message contains a word that should be inserted in the dictionary*/, 
	SEARCH_WORD /*Indicates that the next message contains a search word*/,
	RESULT /**/, 
	ERASE_WORD /*Erase all the words from the dictionary*/,  
	STOP /*End the slave process*/, 
	NO_TYPE /*Indicates that the current message has no type*/
} MessageType;

typedef enum {
	OK, 
	FILE_ERROR
} ExitType;

#define BUFFER_SIZE 250

/*Send an int with the given tag to the given destination, return 1 if send, 0 otherwise*/
int common_send_int(
	int send, 
	MessageType type,
	int destination
);

/*Send a string with the given tag to the given destination, return 1 if send, 0 otherwise*/
int common_send_char(
	char * send, 
	MessageType type, 
	int destination
);

/*Recv an int from any source with any tag, return the int and the type*/
int common_recv_int(
	MessageType * type
);

char * common_recv_char(
	MessageType * type
);

int common_reduce(
	int * send, 
	int * recv,
	MPI_Op op
);

void common_mpi_init(
	int * world_size,
	int * world_rank
);

void common_mpi_end(ExitType type);

#endif /*COMMON_H*/
