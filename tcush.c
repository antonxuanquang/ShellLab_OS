//*********************************************************
//
// PUT YOUR NAME HERE!!!!
// Operating Systems
// Project #1: Writing Your Own Shell: tcush
//
//*********************************************************

//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"
#include "history.h"
#include "forweb.h"
#include "nls.h"
#include "fil.h"
#include "pipe.h"
#define STRMYQUIT "myquit"

//*********************************************************
//
// Type Declarations
//
//*********************************************************

//*********************************************************
//
// Extern Declarations
//
//*********************************************************
extern char **gettoks();

//*********************************************************
//
// Function Prototypes
//
//*********************************************************
bool handleInternal(char **toks);
void handleExternal(char **toks);
bool isBackground(char **toks);
void excuteCommand(char **toks);


//*********************************************************
//
// Global variables
//
//*********************************************************
struct history_node *history_list = NULL;

//*********************************************************
//
// Main Function
//
//*********************************************************
int main(int argc, char *argv[]) {
  int ii;
  char **toks;
  int retval;
  int input;
  int output;
  char *prompt;
  char *username;

  if ((username = getlogin()) == NULL) {
    fprintf(stderr, "Get of user information failed.\n"); exit(1);
  } else {
    prompt = strcat(username, ", don't break the shell > ");
  }

  /* initialize local variables */
  ii = 0;
  toks = NULL;
  retval = 0;

  /* put signal catching functions here */
  signal(SIGINT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);

  while( true ) {
    printf("%s", prompt);

    toks = gettoks(); // get arguments
    if (toks[0] == NULL) continue; // No input
    if (strcmp(toks[0], STRMYQUIT) == 0) break; // Dr. Scherger wants out!

    toks = appendHistoryCommand(history_list, toks);
    push_command(&history_list, toks);

    // Handle internal commands
    if (!handleInternal(toks)) {
      handleExternal(toks);
    }
    
  }

  /* return to calling environment */
  return(retval);
}

bool handleInternal(char **toks) {
  bool isInternal = true;
  char* command = toks[0];

  if (strcmp(command, "history") == 0) {
    print_command(history_list);
  }  else if (strcmp(command, "forweb") == 0) {
    forweb(toks);
  } else if (strcmp(command, "nls") == 0) {
    nls(toks);
  } else if (strcmp(command, "fil") == 0) {
    fil(toks);
  } else {
    isInternal = false;
  }

  return isInternal;
}

void handleExternal(char **toks) {
  int pid = fork();

  // when can't fork more processes
  if (pid < 0) {
    printf("Fork error!!!\n");
    return;
  }

  bool background = isBackground(toks);

  if (pid == 0) {
    int fh_in, fh_out, input, output, is_pipe;
    char *output_filename;
    char *input_filename;
    char **pipe_toks;

    // Check redirected input, output
    input = redirect_input(toks, &input_filename);
    output = redirect_output(toks, &output_filename);
    is_pipe = do_pipe(toks, &pipe_toks);

    if (input == -1 || output == -1) {
      printf("File redirect: systax error\n");
      return;
    }

    // set up redirections
    if (input) {
      if ((fh_in = open(input_filename, O_RDONLY)) == -1) {
        printf("Can't open %s file\n", input_filename);
        return;
      } else {
        dup2(fh_in, 0);
      }
    }
    if (output) {
      if ((fh_out = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 
                      S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1) {
        printf("Can't open %s file\n", output_filename);
        return;
      } else {
        dup2(fh_out, 1);
      }
    }
    
    if (is_pipe) {
      int pfds[2];
      pipe(pfds);
      if (!fork()) {    /* child will execute command before pipe (|)*/
        close(1);       /* close normal stdout */
        dup(pfds[1]);   /* make stdout same as pfds[1] */
        close(pfds[0]); /* we don't need this */
      } else {          /* parent will execute command after pipe (|)*/
        close(0);       /* close normal stdin */
        dup(pfds[0]);   /* make stdin same as pfds[0] */
        close(pfds[1]); /* we don't need this */
        excuteCommand(pipe_toks);
      }
    }

    excuteCommand(toks);
  }

  if (!background && pid > 0) {
    int status;
    waitpid(pid, &status, 0);
  }
}

bool isBackground(char **toks) {
  int i;
  bool isInBackground = false;

  // get the last argument
  for (i = 0; toks[i] != '\0'; i++);
  char *last_command = toks[--i];

  // check the flag. If there is an & in the end, remove the &
  if (strcmp(last_command, "&") == 0 && i >= 1) {
    toks[i] = NULL;
    isInBackground = true;
  }

  return isInBackground;
}

void excuteCommand(char **toks) {
  execvp(toks[0], toks);
  printf("%s -- Command not found\n", toks[0]);
  exit(-1);
}