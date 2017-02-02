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

#define STRMYQUIT "myquit"


//*********************************************************
//
// Type Declarations
//
//*********************************************************
typedef enum{ false, true } bool;


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
bool isInternal(char **toks);
void handleExternal(char **toks);
bool isBackground(char **toks);



//*********************************************************
//
// Main Function
//
//*********************************************************
int main( int argc, char *argv[] )
{
  /* local variables */
  int ii;
  char **toks;
  int retval;
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
  // getlogin_r(prompt, promptBufsize);

  /* put signal catching functions here */
  // signal(SIGINT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  
  /* main (infinite) loop */
  while( true ) {

    /* print prompt*/
    printf("%s", prompt);

    /* get arguments */
    toks = gettoks();
    if( toks[0] != NULL )	{
      /* if want to quit, quit first*/
  	  if( !strcmp( toks[0], STRMYQUIT ))
        break;

      /* if internal commands, execute them,else handle system calls */ 
      if (!isInternal(toks)) {
        handleExternal(toks);
      }
      





      /* simple loop to echo all arguments */
  	  // for( ii=0; toks[ii] != NULL; ii++ ) {
	    //   printf( "Argument %d: %s\n", ii, toks[ii] );
	    // }
  	}
  }

  /* return to calling environment */
  return(retval);
}

bool isInternal(char **toks) {
  bool flag = true;
  char* command = toks[0];
  if (strcmp(command, "history") == 0) {
    printf("%s\n", command);
  }  else if (strcmp(command, "forweb") == 0) {
    printf("%s\n", command);
  } else if (strcmp(command, "nls") == 0) {
    printf("%s\n", command);
  } else if (strcmp(command, "fil") == 0) {
    printf("%s\n", command);
  } else {
    flag = false;
  }
  return flag;
}

void handleExternal(char **toks) {
  int pid = fork();

  // when can't fork more processes
  if (pid < 0) {
    printf("Fork error!!!\n");
    return;
  }

  // in background
  if (isBackground(toks)) {
    if (pid == 0) {
      execvp(toks[0], toks);
      printf("%s -- Command not found\n", toks[0]);  
    }

  // in foreground
  } else {
    if (pid == 0) {
      execvp(toks[0], toks);
      printf("%s -- Command not found\n", toks[0]);  
    } else if (pid > 0){
      wait(NULL);
    }
  }
}

bool isBackground(char **toks) {
  int i;
  bool flag = false;

  // get the last argument
  for (i = 0; toks[i] != '\0'; i++)
    ;
  char *last_command = toks[--i];

  // check the flag. If there is an & in the end, remove the &
  if (strcmp(last_command, "&") == 0 && i >= 1) {
    toks[i] = '\0';
    flag = true;
  }

  return flag;
}