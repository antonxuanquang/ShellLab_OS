#include "nls.h"

void nls(char **toks) {
	DIR *dir;
	struct dirent *file;
	char path[1024];
	
	if (toks[1] == NULL) {
		strcpy(path, ".");
	} else {
		strcpy(path, toks[1]);
	}

	printf("Files: \n");

	// list files
	dir = opendir(path);
	if (dir) {		
		while ((file = readdir(dir)) != NULL) {
			if (file->d_type != DT_DIR) {
				printf("\t%s\n", file->d_name);
			}
		}
	} else {
		printf("Folder not found. Please give correct folder name\n");
		return;
	}
	closedir(dir);

	printf("\n\n");
	printf("Folders: \n");
	// list folders
	dir = opendir(path);
	if (dir) {		
		while ((file = readdir(dir)) != NULL) {
			if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
            	continue;
			if (file->d_type == DT_DIR) {
				printf("\t%s\n", file->d_name);
			}
		}
	} else {
		printf("Folder not found. Please give correct folder name\n");
	}
	closedir(dir);
}         