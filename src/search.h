#ifndef SEARCH_H
#define SEARCH_H

#include "list.h"

struct _SearchNode {
	char * litere;
	NodPtr head, tail;
	struct _SearchNode * left, * right;
	int rezultate;
};
typedef struct _SearchNode SearchNode;

int search_insert(
	SearchNode ** root, 
	Component * component
);

void search_insert_word(
	SearchNode ** root,
	Word * word
);

void search_insert_words(
	SearchNode ** root,
	Word ** words, 
	int count
);

SearchNode * search(
	SearchNode * root, 
	const char * keyWord
);

void search_free(
	SearchNode * root
);

#endif /*SEARCH_H*/
