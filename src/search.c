#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "search.h"

SearchNode * createSearchNode(char * litere) {
	SearchNode * searchNode = malloc(sizeof(SearchNode));
	searchNode->litere = litere;
	searchNode->head = NULL;
	searchNode->tail = NULL;
	searchNode->left = NULL;
	searchNode->right = NULL;
	searchNode->rezultate = 0;
}

void insertNode(SearchNode * node, Component * component);

int search_insert(SearchNode ** root, Component * component) {
	if(*root == NULL) 
		*root = createSearchNode(component_get_component(component));

	insertNode(*root, component);
}

void insertNode(SearchNode * node, Component * component) {
	char * componentText = component_get_component(component);

	if(strcasecmp(componentText, node->litere) < 0) {
		if(node->left == NULL) 
			node->left = createSearchNode(componentText);
		else
			free(componentText);
		insertNode(node->left, component);
	} else if(strcasecmp(componentText, node->litere) > 0) {
		if(node->right == NULL)
			node->right = createSearchNode(componentText);
		else 
			free(componentText);
		insertNode(node->right, component);
	} else { /*if(strcasecmp(componentText, node->litere) == 0)*/
		list_insert(&node->head, &node->tail, component);
		node->rezultate++;
		free(componentText);
	}
}

SearchNode * search(SearchNode * root, const char * litere) {
	if(root == NULL)
		return NULL;
	
	if(strcasecmp(litere, root->litere) == 0)
		return root;
	else if(strcasecmp(litere, root->litere) < 0)
		return search(root->left, litere);
	else
		return search(root->right, litere);
}

void search_free(SearchNode * root) {
	if(root == NULL)
		return;

	//search_free(root->left);
	search_free(root->right);

	NodPtr head = root->head;
	if(head)
		list_free(head);

	free(root->litere);
	
	free(root);
}

void search_insert_word(SearchNode ** root, Word * word) {
	int number_of_components, i;
	Component ** components = component_get_components(word, &number_of_components);

	for(i = 0; i < number_of_components; i++)
		search_insert(root, components[i]);
}

void search_insert_words(SearchNode ** root, Word ** words, int count) {
	int i;
	for(i = 0; i < count; i++)
		search_insert_word(root, words[i]);
}
