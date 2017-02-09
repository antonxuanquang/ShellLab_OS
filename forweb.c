#include "forweb.h"

/*
	
*/

void forweb(char **toks) {
	if (toks[1] == NULL) {
		printf("usage: %s <dirname>\n", toks[0]);
	} else {
		change_permission_rec(toks[1]);
	}
}

/*

	I got this from 
	http://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux

*/
void change_permission_rec(char *path) {
	DIR *dir;
	struct dirent *file;
	dir = opendir(path);
	if (dir) {		
		while ((file = readdir(dir)) != NULL) {
			// compute relative path 
			char file_name[1024];
            int len = snprintf(file_name, sizeof(file_name)-1, "%s/%s", path, file->d_name);
            file_name[len] = 0;

            // getting current mode of the file
            struct stat buffer;
			stat(file_name, &buffer);

            if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            	continue;
			else if (file->d_type == DT_DIR) {
                chmod(file_name, buffer.st_mode | S_IXOTH | S_IROTH);
                change_permission_rec(file_name);
			} else {
				chmod(file_name, buffer.st_mode | S_IROTH);
			}
		}
	}
	closedir(dir);
}