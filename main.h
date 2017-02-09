
#include "history.h"
#include "forweb.h"
#include "nls.h"
#include "fil.h"

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
bool isInternal(char **toks);
void handleExternal(char **toks);
bool isBackground(char **toks);
void excuteCommand(char **toks);