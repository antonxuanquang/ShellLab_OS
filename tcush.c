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
  signal(SIGINT, SIG_IGN);
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

      /* simple loop to echo all arguments */
  	  for( ii=0; toks[ii] != NULL; ii++ ) {
	      printf( "Argument %d: %s\n", ii, toks[ii] );
	    }

  	  
  	}
  }

  /* return to calling environment */
  return(retval);
}
