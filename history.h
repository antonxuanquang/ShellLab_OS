#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct history_node {
	int number;
	char **toks;
	struct history_node* next;
} history_node;

void push_command(struct history_node** head_ref, char **toks);
void print_command(struct history_node* node);
char *join_tokens(char **toks);
char **appendHistoryCommand(struct history_node* head, char **toks);
char **copy_toks(char **toks);
char **append_toks(char **new_toks, char **toks);