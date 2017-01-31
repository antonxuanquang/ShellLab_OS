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
#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

#define STRMYQUIT "myquit"

//*********************************************************
//
// Type Declarations
//
//*********************************************************
using namespace std;


//*********************************************************
//
// Extern Declarations
//
//*********************************************************
using namespace std;
extern "C"
{
  extern char **gettoks();
} 


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
  // local variables
  int ii;
  char **toks;
  int retval;

  // initialize local variables
  ii = 0;
  toks = NULL;
  retval = 0;


  // put signal catching function calls here


  // main (infinite) loop
  while( true )
    {
      // get arguments
      toks = gettoks();

      if( toks[0] != NULL )
	{
	  // simple loop to echo all arguments
	  for( ii=0; toks[ii] != NULL; ii++ )
	    {
	      cout << "Argument " << ii << ": " << toks[ii] << endl;
	    }

	  if( !strcmp( toks[0], STRMYQUIT ))
	    break;
	}
    }

  // return to calling environment
  return( retval );
}
