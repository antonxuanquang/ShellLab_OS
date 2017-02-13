#include <fcntl.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
typedef enum{ false, true } bool;

void fil(char **toks);
int readLine(int fh_in, char* line);
char *trimWhiteSpace(char *str);