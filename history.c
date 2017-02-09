#include "history.h"

void push_command(struct history_node** head_ref, char *command) {
	struct history_node *new_node = (struct history_node*) malloc(sizeof(struct history_node));
	if ((*head_ref) == NULL) {
		new_node->number = 1;
	} else {
		new_node->number = (*head_ref)->number + 1;
	}
	new_node->command = command;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void print_command(struct history_node* node) {
	if (node == NULL) return;
	else {
		print_command(node->next);
		printf("%d: %s\n", node->number, node->command);
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