#include <stdio.h>
#include <dirent.h> 
#include <string.h>
#include <sys/stat.h>
#include "forweb.h"

void forweb(char *name) {
	// struct stat buffer;
	// stat(name, &buffer);
	// chmod(name, buffer.st_mode | S_IROTH | S_IXOTH);
	// chmod(name, )
	change_permission_rec(name);
}

void change_permission_rec(char *name) {
	DIR *dir;
	struct dirent *file;
	dir = opendir(name);
	if (dir) {		
		while ((file = readdir(dir)) != NULL) {
			struct stat buffer;
			if (file->d_type == DT_DIR) {
				char path[1024];
				int len = snprintf(path, sizeof(path)-1, "%s/%s", name, file->d_name);
				path[len] = 0;
				if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
					continue;
				printf("%s\n", path);
				// stat(path, &buffer);
				// chmod(path, buffer.st_mode | S_IROTH | S_IXOTH);
				change_permission_rec(path);
			} else {
				// stat(name, &buffer);
				// chmod(name, buffer.st_mode | S_IROTH | S_IXOTH);
				printf("name: %s\n", name);
			}
		}
	} 
	closedir(dir);
}