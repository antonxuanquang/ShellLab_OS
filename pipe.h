#include "common.h"

// Function prototypes
int redirect_input(char **args, char **input_filename);
int redirect_output(char **args, char **output_filename);
int do_pipe(char **toks, char ***pipe_toks);
