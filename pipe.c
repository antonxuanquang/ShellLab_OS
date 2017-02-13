#include "pipe.h"
#include <stdio.h>
#include <stdlib.h>

// Check for input redirection
int redirect_input(char **args, char **input_filename) {
  for(int i = 0; args[i] != NULL; i++) {

    // Look for the <
    if(args[i][0] == '<') {
      free(args[i]);

      // Read the filename
      if(args[i+1] != NULL) {
	      *input_filename = args[i+1];
      } else {
	       return -1;
      }

      // Adjust the rest of the arguments in the array
      for(int j = i; args[j-1] != NULL; j++) {
	       args[j] = args[j+2];
      }

      return 1;
    }
  }

  return 0;
}

int redirect_output(char **args, char **output_filename) {
  for(int i = 0; args[i] != NULL; i++) {

    // Look for the >
    if(args[i][0] == '>') {
      free(args[i]);

      // Get the filename
      if(args[i+1] != NULL) {
	       *output_filename = args[i+1];
      } else {
	       return -1;
      }

      // Adjust the rest of the arguments in the array
      for(int j = i; args[j-1] != NULL; j++) {
	       args[j] = args[j+2];
      }

      return 1;
    }
  }

  return 0;
}
