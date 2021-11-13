%{
#include "gen.h"
#define TREE_DEBUG 1

extern int line_n;
extern char* yytext;

extern char line1[1024];
extern char line2[1024];
%}

%union
{
    int   ival;
    char* text;
    void* ptr;
}

%token FOR
%token <text> TYPE ID COMP_OP
%token <ival> CONST

%type <ptr> for _operation _condition _assignment operation assignment declaration statement expression action block

%start program

%left '+' '-'
%left '*' '/'
%left NEG

%%
program : TYPE ID '(' ')' '{' block '}'  
        { Tree *tree = makeTree($6); if (TREE_DEBUG) printTree(tree); generateCode($2, tree); }
        ;
        
action : operation ';' { $$ = makeActionOperation($1); }
       | for           { $$ = makeActionFor($1); }
       ;

block : action       { $$ = makeBlock($1, 0); }
      | action block { $$ = makeBlock($1, $2); }
      ;
               
for : FOR '(' _operation ';' _condition ';' _assignment ')' '{' block '}'
    { $$ = makeFor($3, $5, $7, $10); }
    ;
_operation : operation
           | { $$ = 0; }
           ;
_condition : statement
           | { $$ = 0; }
           ;
_assignment : assignment
            | { $$ = 0; }
            ;
            
operation : assignment  { $$ = makeOperationAssignment($1); }
          | declaration { $$ = makeOperationDeclaration($1); }
          ;
assignment : ID '=' expression { $$ = makeAssignment($1, $3); }     
           ;
declaration : TYPE ID                { $$ = makeDeclaration($1, $2, 0); }
            | TYPE ID '=' expression { $$ = makeDeclaration($1, $2, $4); }
            ;
            
statement : expression COMP_OP expression { $$ = makeStatement($1, $2, $3); }
          ;
          
expression : CONST                     { $$ = makeExpressionOperand(makeOperandConst($1)); }
           | ID                        { $$ = makeExpressionOperand(makeOperandId($1)); }
           | '(' expression ')'        { $$ = $2; }
           | expression '-' expression { $$ = makeExpression($1, "-", $3); }
           | expression '+' expression { $$ = makeExpression($1, "+", $3); }
           | expression '/' expression { $$ = makeExpression($1, "/", $3); }
           | expression '*' expression { $$ = makeExpression($1, "*", $3); }
           | '-' expression %prec NEG  { $$ = makeExpression(0, "-", $2); }
           ;
%%

yyerror (char *s) 
{
    fprintf(stderr, "%s%s", line1, line2);
	fprintf(stderr, "<--\nline %d: ?-%s\nUnknown literal: %s\n", line_n, s, yytext); 	
}
