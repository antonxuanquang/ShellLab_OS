#include "fil.h"

void fil(char **toks) {
	int BUFFER_SIZE = 132;
	char BUFFER[BUFFER_SIZE];
	char *from = toks[1];
	char *to = toks[2];
	int fh_in;
	int fh_out;

	if (toks[1] == NULL || toks[2] == NULL) {
		printf("usage: %s [from] [to]\n", toks[0]);
	}
	

	// should be able to open 'from' and 'to' files
	if((fh_in = open(from, O_RDONLY)) == -1) {
		printf("Can't open %s file\n", from);
		return;
	}

	if((fh_out = open(to, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
		printf("Can't open %s file\n", to);
		return;
	}


	int line_count = 0;
	int character_count = 0;
	while(read(fh_in, BUFFER, 1) > 0) {
		char letter = BUFFER[0];
		
		// All trailing blanks at the end of each line are removed.
	

		// All tabs are replaced by an equivalent number of spaces.
		if(letter == '\t') {
			BUFFER[0] = ' ';
		}
		// All BACKSPACE and nonprinting characters are removed.
		else if (isNonPrintingCharacter(letter)) {
			continue;
		}

		character_count++;

		
		// Write the letter to out file
		write(fh_out, BUFFER, 1);

		// All lines longer than 132 characters are folded.
		if (character_count == 132) {
			write(fh_out, "\n", 1);
			character_count = 0;
		}

		// A form fed is added for every 66 lines from the previous form feed.
		if(letter == '\n') {
			line_count++;
			if (line_count == 66) {
				write(fh_out, "\f", 1);
				line_count = 0;
			}
		}
	}

	close(fh_in);
	close(fh_out);
}

bool isNonPrintingCharacter(char letter) {
	return letter == '\b';
}