#include "component.h"

Component ** component_get_components(Word * word, int * number_of_components) {
	int m = strlen(word->word);
	*number_of_components = (m * (m+1) ) / 2;

	Component ** components = (Component **) malloc( *number_of_components * sizeof(Component *) );
	Component * buffer;
	int pas, i, index = 0;

	for(pas = 1; pas <= m; pas++) {
		for(i = 0; i < (m - pas + 1); i++) {
			buffer = malloc(sizeof(Component));
			buffer->word = word;
			buffer->size = pas;
			buffer->relative_index = i;

			components[index++] = buffer;
		}
	}

	return components;
}

char * component_to_string(const Component * component) {
	const char * c_word = component->word->word;
	int len = strlen(c_word)+1, i;
	char * word = (char *) malloc( len * sizeof(char) );
	char * result = (char *) malloc(50 * sizeof(char) );	//TODO: nu 50
	
	strcpy(word, c_word);

	//Make everything to lower case
	for(i = 0; i < len; i++)
		word[i] = tolower(word[i]);

	//Make the component to upper case
	for(i = 0; i < component->size; i++)
		word[component->relative_index + i] = toupper(word[component->relative_index + i]);

	sprintf(result, "\"%s\" - at row %d, index %d.", word, component->word->row, component->word->index);

	free(word);

	return result;
}

char * component_get_component(const Component * component) {
	char * result = malloc(component->size * sizeof(char));
	
	strncpy( result, &(component->word->word[component->relative_index]), component->size);
	
	return result;
}

void component_free(Component * component) {
	free(component);
}
