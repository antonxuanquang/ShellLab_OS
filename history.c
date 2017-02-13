#include "history.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// private function proto
char **copy_toks(char **toks);
char **append_toks(char **new_toks, char **toks);
char *join_tokens(char **toks);

void push_command(struct history_node** head_ref, char **toks) {
	struct history_node *new_node = (struct history_node*) malloc(sizeof(struct history_node));
	if ((*head_ref) == NULL) {
		new_node->number = 1;
	} else {
		new_node->number = (*head_ref)->number + 1;
	}
	new_node->toks = copy_toks(toks);
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

char **copy_toks(char **toks) {
	int i;
	int size;

	// allocate correct number of toks
	for (i = 0; toks[i] != NULL; i++);
	size = i;
	char **new_toks = (char **) malloc(sizeof(char *) * size);
	

	// copy toks to new array of tokens
	for (i = 0; toks[i] != NULL; i++) {
		int length = strlen(toks[i]);
		new_toks[i] = (char *) malloc(sizeof (char) * length);
		strcpy(new_toks[i], toks[i]);
	}
	new_toks[i] = NULL;
	return new_toks;
}

void print_command(struct history_node* node) {
	if (node == NULL) return;
	else {
		print_command(node->next);
		printf("%d: %s\n", node->number, join_tokens(node->toks));
	}
}

char *join_tokens(char **toks) {
	char *command = (char*) malloc(sizeof(char) * 80);
	strcpy(command, toks[0]);
	int i;
	for (i = 1; toks[i] != '\0'; i++) {
		strcat(command, " ");
		strcat(command, toks[i]);
	}
	return command;
}

char **appendHistoryCommand(struct history_node* head, char **toks) {
	// return null if there is no ! in the first token
	// also return null if history linnked list is not initialized
	if (strcmp(toks[0], "!") != 0 || head == NULL) {
		return toks;
	}


	// return the last called command if !!
	if (strcmp(toks[1], "!") == 0) {
		char ** result = append_toks(head->toks, toks);
		return result;
	} 

	
	int number;
	// invalid syntax right here
	if ((number = atoi(toks[1])) == 0) {
		return toks;
	}

	struct history_node* node = head;
	// looking for the command with number = tok[1]
	while (node != NULL) {
		if (node->number == number) {
			char ** result = append_toks(node->toks, toks);
			return result;
		}
		node = node->next;
	}
	return toks;
}

char **append_toks(char **new_toks, char **toks) {

	int i, j;
	int size = 0;

	// allocate correct number of toks
	for (i = 2; toks[i] != NULL; i++) {
		size++;
	}

	for (i = 0; new_toks[i] != NULL; i++) {
		size++;
	}
	char **result = (char **) malloc(sizeof(char *) * size);

	size = 0;
	// copy toks to new array of tokens
	for (i = 0; new_toks[i] != NULL; i++) {
		int length = strlen(new_toks[i]);
		result[size] = (char *) malloc(sizeof(char) * length);
		strcpy(result[size], new_toks[i]);
		size++;
	}

	for (i = 2; toks[i] != NULL; i++) {
		int length = strlen(toks[i]);
		result[size] = (char *) malloc(sizeof(char) * length);
		strcpy(result[size], toks[i]);
		size++;
	}

	result[size] = NULL;
	return result;
}