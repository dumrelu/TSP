#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include "component.h"


struct Nod {
  Component * info;
  struct Nod * next;
};

typedef struct Nod * NodPtr;


void list_insert(
	NodPtr * head, 
	NodPtr * tail, 
	Component * info
);

int list_delete(
	NodPtr * head, 
	NodPtr * tail, 
	char * word
);

int list_delete_all(
	NodPtr * head,
	NodPtr * tail, 
	char * word
);

void list_print(
	NodPtr head
);

void list_free_node(
	NodPtr node
);

void list_free(
	NodPtr head
);

#endif /*LIST_H*/
