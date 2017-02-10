#include "history.h"
#include "forweb.h"
#include "nls.h"
#include "fil.h"
#include "pipe.h"

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
void handleExternal(char **toks, int input, char *input_filename, int output,
               char *output_filename);
bool isBackground(char **toks);
void excuteCommand(char **toks);
