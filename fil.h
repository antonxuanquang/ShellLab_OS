#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef enum{ false, true } bool;

void fil(char **toks);
bool isNonPrintingCharacter(char letter);