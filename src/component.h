#ifndef COMPONENT_H
#define COMPONENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "word.h"

typedef struct {
	Word * word;
	int relative_index;
	int size;
} Component;

/*Returns all posible components of the word
 Ex: 
	word:
	    1 letter components: "w", "o", "r", "d"
	    2 letter components: "wo", "or", "rd"
	    3 letter components: "wor", "ord"
	    4 letter components: "word"
Number of components: ( m * (m+1) ) / 2, where m = strlen("word");
*/
Component ** component_get_components(
	Word * word /*The word*/, 
	int * number_of_components /*It will contain the number of components in the array*/
);

char * component_to_string(
	const Component * component
);

char * component_get_component(
	const Component * component
);

void component_free(
	Component * component
);

#endif /*COMPONENT_H*/
