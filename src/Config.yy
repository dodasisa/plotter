%skeleton "lalr1.cc"
%require "3.7.4"
%language "C++"
%debug 
%defines 
%define api.namespace {MC}
%define parser_class_name {MC_Parser}
 
%code requires{
   namespace MC {
      class MC_Driver;
      class MC_Scanner;
   }
 
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

%parse-param { MC_Scanner  &scanner  }
%parse-param { MC_Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "mc_driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token	END    0     "end of file"
%token	LED
%token	SERVO
%token	BUTTON
%token	CAMERA
%token	DOT

%locations

%%

list_option : END | list END;
 
list   
  : %empty
  | list line
  ;
 
line    
  : EOL                                                          { std::cerr << "Empty line.\n"; }
  | NAME ASSIGN TEXT                                             { driver.addValue($1,$3);       }
  | NAME ASSIGN COMPONENT DOT TYPE ( LED ) DOT PIN ( NUMBER )    { driver.addLed($1,$12);        }
  | NAME ASSIGN COMPONENT DOT TYPE ( BUTTON ) DOT PIN ( NUMBER ) { driver.addButton($1,$12);     }
  | NAME ASSIGN COMPONENT DOT TYPE ( CAMERA )                    { driver.addCamera($1);         }
  | NAME ASSIGN COMPONENT DOT TYPE ( SERVO ) DOT PIN ( NUMBER )  { driver.addServo($1,$12);      }
  ;
 
%%
namespace yy
{
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
