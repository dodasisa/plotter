%skeleton "lalr1.cc"
%require "3.7.5"
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

%token               END    0     "end of file"
%token               LED
%token               SERVO
%token               BUTTON
%token               CAMERA
%token               DOT
%token               ASSIGN
%token               COMPONENT
%token               PIN
%token               OPEN_BRACKET
%token               CLOSE_BRACKET
%token               COMPONENT
%token               TYPE
%token <std::string> TEXT
%token <std::string> NAME
%token int           NUMBER

%locations

%%

list_option : END | list END;
 
list   
  : %empty
  | list line
  ;
 
line    
  : EOL                                                                                                        { std::cerr << "Empty line.\n"; }
  | NAME ASSIGN TEXT                                                                                           { driver.addValue($1,$3);       }
  | NAME ASSIGN COMPONENT DOT TYPE OPEN_BRACKET LED CLOSE_BRACKET DOT PIN OPEN_BRACKET NUMBER CLOSE_BRACKET    { driver.addLed($1,$12);        }
  | NAME ASSIGN COMPONENT DOT TYPE OPEN_BRACKET BUTTON CLOSE_BRACKET DOT PIN OPEN_BRACKET NUMBER CLOSE_BRACKET { driver.addButton($1,$12);     }
  | NAME ASSIGN COMPONENT DOT TYPE OPEN_BRACKET CAMERA CLOSE_BRACKET                                           { driver.addCamera($1);         }
  | NAME ASSIGN COMPONENT DOT TYPE OPEN_BRACKET SERVO CLOSE_BRACKET DOT PIN OPEN_BRACKET NUMBER CLOSE_BRACKET  { driver.addServo($1,$12);      }
  ;
 
%%
void 
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
