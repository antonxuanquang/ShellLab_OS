#include "forweb.h"

/*
	
*/

void forweb(char **toks) {
	// if (toks[1] == NULL) {
	// 	printf("usage: %s <dirname>\n", toks[0]);
	// } else {
	// 	change_permission_rec(toks[1]);
	// }
	if (toks[1] == NULL) {
		ftw(".", list, 1);
	} else if (ftw(toks[1], list, 1) == -1){
		printf("Can't open folder '%s'\n", toks[1]);
	}
}

int list(const char *name, const struct stat *status, int type) {
	if(type == FTW_NS)
		return -1;

	if(type == FTW_F) {
		// printf("0%3o\t%s\n", status->st_mode&0777, name);
		chmod(name, status->st_mode | S_IROTH | S_IRGRP);
	}
		
	if(type == FTW_D && strcmp(".", name) != 0) {
		chmod(name, status->st_mode | S_IXOTH | S_IROTH | S_IXGRP | S_IRGRP);
		// printf("0%3o\t%s/\n", status->st_mode&0777, name);
	}

	return 0;
}

/*

	I got this from 
	http://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux

*/
// void change_permission_rec(char *path) {
// 	DIR *dir;
// 	struct dirent *file;
// 	dir = opendir(path);
// 	if (dir) {		
// 		while ((file = readdir(dir)) != NULL) {
// 			// compute relative path 
// 			char file_name[1024];
//             int len = snprintf(file_name, sizeof(file_name)-1, "%s/%s", path, file->d_name);
//             file_name[len] = 0;

//             // getting current mode of the file
//             struct stat buffer;
// 			stat(file_name, &buffer);

//             if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
//             	continue;
// 			else if (file->d_type == DT_DIR) {
//                 chmod(file_name, buffer.st_mode | S_IXOTH | S_IROTH);
//                 change_permission_rec(file_name);
// 			} else {
// 				chmod(file_name, buffer.st_mode | S_IROTH);
// 			}
// 		}
// 	}
// 	closedir(dir);
// }