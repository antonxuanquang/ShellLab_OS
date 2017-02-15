#include "pipe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Check for input redirection
int redirect_input(char **args, char **input_filename) {
  int i;
  for(i = 0; args[i] != NULL; i++) {

    // Look for the <
    if(args[i][0] == '<') {
      free(args[i]);

      // Read the filename
      if(args[i+1] != NULL) {
	      *input_filename = args[i+1];
      } else {
	       return -1;
      }
      int j; 
      // Adjust the rest of the arguments in the array
      for(j = i; args[j-1] != NULL; j++) {
	       args[j] = args[j+2];
      }

      return 1;
    }
  }

  return 0;
}

int redirect_output(char **args, char **output_filename) {
  int i;
  for(i = 0; args[i] != NULL; i++) {

    // Look for the >
    if(args[i][0] == '>') {
      free(args[i]);

      // Get the filename
      if(args[i+1] != NULL) {
	       *output_filename = args[i+1];
      } else {
	       return -1;
      }
      int j;
      // Adjust the rest of the arguments in the array
      for(j = i; args[j-1] != NULL; j++) {
	       args[j] = args[j+2];
      }

      return 1;
    }
  }

  return 0;
}

int do_pipe(char **toks, char ***pipe_toks) {
  int i;
  for (int i = 0; toks[i] != NULL; i++) {
    if (strcmp(toks[i], "|") == 0) {
      *pipe_toks = toks + (i + 1);
      toks[i] = NULL;
      return 1;
    }
  }
  return 0;
}
