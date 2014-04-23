#include "word.h"

Word * word_make(const char * text , int * index, int row) {
	Word * result = (Word *) malloc( sizeof(Word) );
	int endIndex; //Ending index of the word
	int text_length = strlen(text)+1;

	if(*index >= text_length) 
		return NULL;

	//Find the starting index of the word
	for(; isspace(text[*index]) || ispunct(text[*index]); (*index)++);


	//Find the ending index of the word
	for(endIndex = *index; !isspace(text[endIndex]) && !ispunct(text[endIndex]); endIndex++);
	
	//Create the word
	result->word = malloc( (endIndex - *index + 1) * sizeof(char) );
	strncpy( result->word, &text[*index], endIndex-*index);	//copy the word from the text
	result->word[endIndex - *index] = '\0';
	result->row = row;
	result->index = *index;
	
	//Find the next word
	for(; isspace(text[endIndex]) || ispunct(text[endIndex]) || endIndex == text_length; (endIndex)++);

	//Update index
	*index = endIndex;

	if(endIndex >= text_length)
		*index = -1;

	return result;
}

Word ** word_make_all(const char * text, int row, int * num_of_words) {
	Word ** words = (Word **) malloc( sizeof(Word*) );
	int index = 0;
	int n = 1;
	
	do {
		words = (Word **) realloc( words, n * sizeof(Word*));
		words[n-1] = word_make(text, &index, row);
		if(index != -1)
			n++;
	} while(index != -1);

	//Set the number of words
	*num_of_words = n;

	return words;
}

char * word_to_string(const Word * word) {
	char * text = (char *) malloc( 50 * sizeof(char) );	//TODO: not 50
	sprintf(text, "\"%s\" - at row %d, index %d.", word->word, word->row, word->index);
	return text;
}

void word_free(Word * word) {
	free(word->word);
	free(word);
}
