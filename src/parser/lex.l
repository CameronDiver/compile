%{
	#include <stdio.h>
	#include "parse.tab.hpp"
	void yyerror(char *);

	char *strVal;
	#define INIT strVal = yytext
%}


digit						[0-9]
alpha						[a-zA-Z]

bindigit					[10]
hexdigit					[0-9a-fA-F]

symbol						[a-zA-Z_]+(alpha|digit)*

/* Taken from https://www.lysator.liu.se/c/ANSI-C-grammar-l.html */
string						\"(\\.|[^\\"])*\"

%%


{bindigit}+"b"				{INIT;return BININT;}
"0x"{hexdigit}+				{INIT;return HEXINT;}
{digit}+					{INIT;return DECINT;}
{digit}*"."{digit}+			{INIT;return FLOAT;}

{symbol}					{INIT;return SYMBOL;}
{string}					{INIT;return STRING;}





%%

int yywrap(void) {
	return 1;
}