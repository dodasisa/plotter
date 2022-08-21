namespace CP
{
	class CP_Scanner : public yyFlexLexer
	{
		public:
			CP_Scanner(std::istream& arg_yyin, std::ostream& arg_yyout): yyFlexLexer(arg_yyin, arg_yyout) {}
			CP_Scanner(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr): yyFlexLexer(arg_yyin, arg_yyout) {}
			int lex(Parser::semantic_type *yylval); // note: this is the prototype we need
	}
}
