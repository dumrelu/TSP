#include "master.h"
#include <time.h>

MessageType IGNORE_TYPE = NO_TYPE;

void master_run(int argc, char ** argv, int world_size, int world_rank) {
	//TODO: filename din argv

	//Read file name
	char filename[50];
	int i;
	printf("Filename: ");
	scanf("%s", filename);

	//Send file to slaves
	master_send_file(filename, world_size);
	

	//Search words
	char word[50];
	for( ; ; ) {
		printf("Keyword(\".\" = STOP): ");
		scanf("%s", word);

		if(strcmp(word, ".") == 0)
			break;
	
		master_search(word, world_size);
	}

	for(i = 1; i < world_size; i++)
		common_send_char("STOP", STOP, i);
}


void master_send_file(const char * filename, int world_size) {
	FILE * file = fopen(filename, "r");
	int slaves = world_size-1;
	
	if(!file)
		common_mpi_end(FILE_ERROR);

	char * line;
	size_t len;
	int row = 0;

	while (getline(&line, &len, file) != -1) {
		if(len > BUFFER_SIZE)	//TODO: split
			common_mpi_end(FILE_ERROR);
		common_send_char(line, ADD_LINE, row % slaves + 1);
		row++;
	}

	free(line);
	fclose(file);
}

void master_search(char * keyword, int world_size) {
	//Start timer	
	/*struct timespec start, end;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);*/
	double t = MPI_Wtime();

	int i;

	//Send keyword
	for(i = 1; i < world_size; i++)
		common_send_char(keyword, SEARCH_WORD, i);

	//Get number of results
	int number_of_results = 0;
	common_reduce(NULL, &number_of_results, MPI_SUM);

	//Recv results
	char ** results = (char **) malloc(number_of_results * sizeof(char *));
	for(i = 0; i < number_of_results; i++)
		results[i] = common_recv_char(&IGNORE_TYPE);

	//End timer
	/*clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	double t = (double)(end.tv_sec - start.tv_sec) * 1.0e9 + (double)(end.tv_nsec - start.tv_nsec);*/
	t = MPI_Wtime() - t;

	//Print results
	//printf("%d result(s) found in %.2lf milliseconds.\n", number_of_results, t / 1000000);
	printf("%d result(s) found in %f milliseconds.\n", number_of_results, t*1000);
	for(i = 0; i < number_of_results; i++) {
		printf("\t->%s\n", results[i]);
		free(results[i]);
	}

	free(results);
}
