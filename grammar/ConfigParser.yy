%skeleton "lalr1.cc"
%require "3.7.5"
%language "C++"
%debug 
%defines 
%define api.namespace {CP}
%define api.parser.class {CP_Parser}
 
%code requires{
   namespace CP {
      class CP_Driver;
      class CP_Scanner;
   }

 
#ifndef YY_NULLPTR
 #if defined __cplusplus && 201103L <= __cplusplus
  #define YY_NULLPTR nullptr
 #else
  #define YY_NULLPTR 0
 #endif
#endif
}

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
%token               EOL
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
%token               TYPE
%token <std::string> TEXT
%token <std::string> NAME
%token               NUMBER

%locations

%%

list_option 
  : END 
  | list END;
 
list   
  : %empty
  | list line
  ;
 
line    
  : EOL                                                                                                        { std::cerr << "Empty line.\n"; }
  | NAME ASSIGN TEXT                                                                                           { driver.addValue($1,$3);       }
  | NAME ASSIGN COMPONENT parameters 
  ;

parameters
  : parameter
  | parameters parameter
  ;

parameter
  : DOT TYPE OPEN_BRACKET comp_type CLOSE_BRACKET
  | DOT PIN OPEN_BRACKET NUMBER CLOSE_BRACKET
  ;
  
comp_type
  : LED
  | BUTTON
  | CAMERA
  | SERVO
  ;
  
  

 
%%
void 
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
