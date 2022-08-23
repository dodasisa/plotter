%{
#include "ConfigParser.hpp"
#include "ConfigScanner.hpp"
#define YY_DECL int calc::Scanner::lex(calc::Parser::semantic_type *yylval)
%}
 
%option c++ interactive noyywrap noyylineno nodefault outfile="Scanner2.cpp"
 
dseq            ([[:digit:]]+)
integer         ({dseq})
text            ([a-zA-Z0-9 ]+)
name            ([a-zA-Z0-9]+)

%%
 
{integer}       yylval->emplace<long long>(strtoll(YYText(), nullptr, 10)); return Parser::token::NUMBER;
"("             return Parser::token::OPEN_BRACKET;
")"             return Parser::token::CLOSE_BRACKET;
"."             return Parser::token::DOT;
"type"          return Parser::token::TYPE;
"led"           return Parser::token::LED;
"servo"         return Parser::token::SERVO;
"camera"        return Parser::token::CAMERA;
"button"        return Parser::token::BUTTON;
"="             return Parser::token::ASSIGN;
{name}          return Parser::token::NAME
{text}          return Parser::token::TEXT
\n              return Parser::token::EOL;
<<EOF>>         return Parser::token::END;
.               /* no action on unmatched input */
 
%%
 
int yyFlexLexer::yylex() {
    throw std::runtime_error("Bad call to yyFlexLexer::yylex()");
}
 
int main() {
    calc::Scanner scanner{ std::cin, std::cerr };
    calc::Parser parser{ &scanner };
    std::cout.precision(10);
    parser.parse();
}
