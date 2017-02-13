#include "common.h"
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
char **appendHistoryCommand(struct history_node* head, char **toks);