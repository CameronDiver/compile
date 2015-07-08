%{
	#include <stdio.h>

	#include "nodes/nodes.h"

	#ifndef YYSTYPE
         #define YYSTYPE SyntaxTreeNode*
    #endif

	#include "parse.tab.hpp"
	void yyerror(char *);

	// extern YYSTYPE yylval;
%}

%option yylineno

digit						[0-9]
alpha						[a-zA-Z]

bindigit					[10]
hexdigit					[0-9a-fA-F]

symbol						[a-zA-Z_]+(alpha|digit)*

/* Taken from https://www.lysator.liu.se/c/ANSI-C-grammar-l.html */
string						\"(\\.|[^\\"])*\"

whitespace					[ \t\r]+

%%


{bindigit}+"b"				{yylval = new Integer(yytext, 2); return BININT;}
"0x"{hexdigit}+				{yylval = new Integer(yytext, 16); return HEXINT;}
{digit}+					{yylval = new Integer(yytext); return DECINT;}
{digit}*"."{digit}+			{yylval = new Float(yytext); return FLOAT;}

{string}					{yylval = new String(yytext); return STRING;}

"int"						{return INTEGER_32;}
"uint"						{return UINTEGER_32;}
"int8"						{return INTEGER_8;}
"uint8"						{return UINTEGER_8;}
"int16"						{return INTEGER_16;}
"uint16"					{return UINTEGER_16;}
"int32"						{return INTEGER_32;}
"uint32"					{return UINTEGER_32;}
"int64"						{return INTEGER_64;}
"uint64"					{return UINTEGER_64;}
"bool"						{return BOOLNAME;}
"float"						{return FLOATNAME;}
"double"					{return DOUBLENAME;}
"string"					{return STRINGNAME;}
"char"						{return CHARNAME;}
"void"						{return VOIDNAME;}


"if"						{return IF;}
"while"						{return WHILE;}
"else"						{return ELSE;}
"end"						{return END;}

"+"							{return PLUS;}
"-"							{return MINUS;}
"*"							{return MULT;}
"/"							{return DIV;}
"%"							{return MOD;}

"="							{return EQUALS;}

"++"						{return INCREMENT;}
"--"						{return DECREMENT;}

"=="						{return COMP;}
"<="						{return LTE;}
">="						{return GTE;}
"!="						{return NOTEQ;}
"<"							{return LT;}
">"							{return GT;}

"+="						{return PLUSEQ;}
"-="						{return MINUSEQ;}
"*="						{return MULTEQ;}
"/="						{return DIVEQ;}

">>"						{return SHR;}
"<<"						{return SHL;}

"or"						{return OR;}
"and"						{return AND;}
"&&"						{return AND;}
"not"						{return NOT;}
"!"							{return NOT;}
"~"							{return BITWISENOT;}



"||"						{return OR;}

"{"							{return LBRACE;}
"}"							{return RBRACE;}

{symbol}					{yylval = new Symbol(yytext); return SYMBOL;}
"\n"						{return NEWLINE;}
{whitespace}				{/* Do Nothing */}

.							{return *yytext;}






%%

int yywrap(void) {
	return 1;
}