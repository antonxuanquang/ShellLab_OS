#include "fil.h"

// private function proto
int readLine(int fh_in, char* line);
char *trimWhiteSpace(char *str);

void fil(char **toks) {
	int LINE_SIZE = 132;
	size_t BUFFER_SIZE = 1024;
	char line[BUFFER_SIZE];
	int FORM_SIZE = 66;
	int fh_in;
	int fh_out;
	int line_count = 0;
	int character_count = 0;

	if (toks[1] == NULL || toks[2] == NULL) {
		printf("usage: %s [from] [to]\n", toks[0]);
	}
	

	// should be able to open 'from' and 'to' files
	if((fh_in = open(toks[1], O_RDONLY)) == -1) {
		printf("Can't open %s file\n", toks[1]);
		return;
	}

	if((fh_out = open(toks[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
		printf("Can't open %s file\n", toks[2]);
		return;
	}


	
	while(readLine(fh_in, line) > 0) {
		// All trailing blanks at the end of each line are removed.
		char *trimLine = trimWhiteSpace(line);

		int len = strlen(trimLine);
		int i;
		for (i = 0; i < len; i++) {

			character_count++;

			// All tabs are replaced by an equivalent number of spaces.
			if (trimLine[i] == '\t') {
				trimLine[i] = ' ';

			//  All BACKSPACE and nonprinting characters are removed.
			} else if (!isprint(trimLine[i]) && trimLine[i] != ' ') {
				continue;
			}

			write(fh_out, &trimLine[i], 1);

			// All lines longer than 132 characters are folded.
			if (character_count == 132) {
				line_count++;
				write(fh_out, "\n", 1);
				character_count = 0;
				if (line_count == 66) {
					write(fh_out, "\f", 1);
					line_count = 0;
				}
			}

		}

		// A form fed is added for every 66 lines from the previous form feed.
		line_count++;
		write(fh_out, "\n", 1);
		character_count = 0;
		if (line_count == 66) {
			write(fh_out, "\f", 1);
			line_count = 0;
		}
	}

	close(fh_in);
	close(fh_out);
}

int readLine(int fh_in, char* line) {
	int count = 0;
	char BUFFER[1];
	while (read(fh_in, BUFFER, 1) > 0) {
		line[count] = BUFFER[0];
		count++;
		if(BUFFER[0] == '\n' || BUFFER[0] == EOF) {
			break;
		}
	}
	line[count] = '\0';
	return count;
}


/*
	I got this from 
	http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
*/
char *trimWhiteSpace(char *str) {
	char *end;

	if(*str == 0)  // All spaces?
	return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace((unsigned char)*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}