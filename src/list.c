#include "list.h"

void list_insert(NodPtr* head, NodPtr* tail, Component * info) {
  NodPtr nodNou = malloc(sizeof(NodPtr));
  nodNou->info = info;
  
  if(!(*head)) 
    *head = *tail = nodNou;
  else {
    (*tail)->next = nodNou;
    (*tail) = nodNou;
  }
}

int list_delete(NodPtr* head, NodPtr* tail, char * word) { 
  if(*head == NULL && *tail == NULL)
    return 0;
  NodPtr buffer = *head;
  
  if(strcasecmp(buffer->info->word->word, word) == 0) { 
    if(*head == *tail)
      *head = *tail = NULL;
    else
      *head = buffer->next;
    
    list_free_node(buffer);
    return 1;
  }
  
  for(;buffer->next && strcasecmp(buffer->next->info->word->word, word) != 0; buffer = buffer->next);	
  
  if(buffer->next) {
      if(buffer->next == *tail) {
	*tail = buffer;
	list_free_node(buffer->next);
      }
      else {
	NodPtr ceva = buffer->next;
	buffer->next = buffer->next->next;
	list_free_node(ceva);
      }
      
      
      return 1;
  }
  
  return 0;
}

int list_delete_all(NodPtr* head, NodPtr* tail, char * word) {	//TODO: solutie temporara, prea complexa
	int deleted = 0;
	
	while(list_delete(head, tail, word))
		deleted++;

	return deleted;
}

void list_print(NodPtr head) {
	char * buffer;
	for(;head;head = head->next) {
		buffer = component_to_string(head->info);
		printf("%s\n", buffer);
		free(buffer);
	}
}

void list_free_node(NodPtr node) {
	component_free(node->info);
	free(node);
}

void list_free(NodPtr head) {
	while(head) {
		NodPtr buffer = head->next;
		//word_free(head->info->word);
		list_free_node(head);
		head = buffer;
	}
}
