#ifndef PARSE_OPERATORS_H
#define PARSE_OPERATORS_H

#include <string>

typedef enum {
	OP_PLUS,
	OP_MINUS,
	OP_MULT,
	OP_DIV,
	OP_MOD,

	OP_COMP,
	OP_LTE,
	OP_GTE,
	OP_NEQ,

	OP_LT,
	OP_GT,

	OP_PLUSEQ,
	OP_MINUSEQ,
	OP_MULTEQ,
	OP_DIVEQ,
	OP_ASSIGN

} Operator;

typedef enum {
	UNARY_NOT,
	UNARY_BNOT,
	UNARY_PREINC,
	UNARY_PREDEC,
	UNARY_POSTINC,
	UNARY_POSTDEC,
	UNARY_PLUS,
	UNARY_MINUS
} UnaryOperator;


std::string opToStr(Operator op);
std::string unaryOpToStr(UnaryOperator op);


#endif