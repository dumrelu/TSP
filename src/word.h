#ifndef WORD_H
#define WORD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
	char * word;	/*The word*/
	int row;	/*What row do you find the word at*/
	int index;	/*There in the row is the word starting*/
} Word;

/*Returns a Word struct formed with the first word from the given text starting from the given index and updates index to the position
of the next word*/
Word * word_make(
	const char * text /*Source text*/, 
	int * index /*Start index*/, 
	int row /*The row on which the word can be found*/
);

/*Returns an array of all the words in the given text*/
Word ** word_make_all(
	const char * text /*Source text*/, 
	int row /*The row on which the word can be found*/, 
	int * num_of_words /*Number of words in the array*/
);

/*Returns a string representation of the given Word*/
char * word_to_string(
	const Word * word /*The word struct*/
);

/*Free memory*/
void word_free(
	Word * word
);

#endif /*WORD_H*/
