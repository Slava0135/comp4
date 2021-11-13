%{
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"

int line_n = 1;

char line1[1024];
char line2[1024];

#define YY_USER_ACTION { strcat(line2, yytext); }
%}

SYM	[A-Za-z_]
DIG	[0-9]
COP ">"|"<"|">="|"<="|"!="|"=="

%START comment

%%
<INITIAL>for                     { return FOR; }
<INITIAL>int                     { yylval.text = strdup(yytext); return TYPE; }
<INITIAL>{SYM}({SYM}|{DIG})*     { yylval.text = strdup(yytext); return ID; }
<INITIAL>"/"|"+"|"*"|"-"         { return yytext[0]; }
<INITIAL>{COP}                   { yylval.text = strdup(yytext); return COMP_OP; }
<INITIAL>{DIG}+                  { yylval.ival = atoi(yytext); return CONST; }
<INITIAL>[ \t]                   ;
"//"                             { BEGIN comment; }
\n                               { line_n++; BEGIN INITIAL; strcpy(line1, line2); line2[0] = '\0'; }
<comment>.                       ;
<INITIAL>.	                     { return yytext[0]; }
%%

#ifndef yywrap
int yywrap() { return 1; }
#endif
