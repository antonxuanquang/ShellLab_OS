#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <sys/stat.h>
#include <ftw.h>
#include <unistd.h>

void forweb(char **toks);
void change_permission_rec(char *name);
int list(const char *name, const struct stat *status, int type);