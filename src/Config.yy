%{
#include <iostream>
#include <string>
#include "Scanner1.hpp"
%}
 
%require "3.7.4"
%language "C++"
%defines "Parser1.hpp"
%output "Parser1.cpp"
 
%define api.parser.class {Parser}
%define api.namespace {config}
%define api.value.type variant
%param {yyscan_t scanner}
 
%code provides
{
    #define YY_DECL \
        int yylex(config::Parser::semantic_type *yylval, yyscan_t yyscanner)
    YY_DECL;
}
 
%token	END
%token	LED
%token	SERVO
%token	BUTTON
%token	CAMERA
%token	DOT
 
%%
 
lines   : %empty
        | lines line
        ;
 
line    : EOL                       { std::cerr << "Read an empty line.\n"; }
        | name ASSIGN value         { std::cout << $1 << '\n'; }
        | error EOL                 { yyerrok; }
        ;
 
name    : NAME                       { $$ = $1; }
	;
 
value   : TEXT                      { $$ = $1; }
        | COMPONENT PARAMS          { $$ = $1 + $3; }
        ;

PARAMS	: PARAM
	| PARAMS PARAM
	;
		
PARAM	: DOT KIND ( VALUE )
	;

KIND	: LED
	| CAMERA
	| SERVO
	| BUTTON
	;
 
%%
namespace yy
{
  // Report an error to the user.
  auto parser::error (const std::string& msg) -> void
  {
    std::cerr << msg << '\n';
  }
}

int main ()
{
  yy::parser parse;
  return parse ();
}
