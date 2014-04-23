#include "slave.h"

void slave_run(int world_size, int world_rank) {
	SearchNode * root = NULL;
	
	MessageType type;
	char * buffer;

	for( ; ; ) {
		buffer = common_recv_char(&type);

		if(type == ADD_LINE) {
			static int row = 0;
			slave_add_line(&root, buffer, row++ * (world_size-1) + (world_rank-1));
		}
		else if(type == SEARCH_WORD)
			slave_search(root, buffer);
		else
			break;
		
		free(buffer);
	}
}

void slave_add_line(SearchNode ** root, char * line, int row) {
	Word * word;
	Component ** components;
	int index = 0;

	do {
		word = word_make(line, &index, row);
		search_insert_word(root, word);
	} while(index != -1);
}

void slave_search(SearchNode * root, const char * keyword) {
	SearchNode * result = search(root, keyword);
	int number_of_results = (result != NULL) ? result->rezultate : 0;

	//Send number of results
	common_reduce(&number_of_results, NULL, MPI_SUM);

	//Send results
	if(!result)
		return;
	NodPtr head = result->head;
	char * buffer;
	for( ; head ; head = head->next) {
		buffer = component_to_string(head->info);
		common_send_char(buffer, RESULT, MASTER);
		free(buffer);
	}
}
