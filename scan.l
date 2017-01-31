%{
  #include <string.h>

  int _numtoks = 100;
  char *_toks[100];
  int _tokcount = 0;
%}

WORD [a-zA-Z0-9\/\.-]+
SPECIAL [!()><|&;*]
QUOTESTR \"([^\\\"]|\\.)*\"

%%
     _tokcount = 0;
     _toks[0] = NULL;

{WORD}|{SPECIAL}|{QUOTESTR} {
         if( _tokcount < _numtoks-1) {
           _toks[_tokcount++] = (char*)strdup(yytext);
           _toks[_tokcount] = NULL;
         }
       }



\n     return( _tokcount );    

[ \t]+

<<EOF>> 
.

%%

char **gettoks() {
  yylex();
  return (char **) _toks;
}


