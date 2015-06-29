#ifndef PARSE_TYPE_H
#define PARSE_TYPE_H

#include "node.h"

class Type : public SyntaxTreeNode {
 public:
	typedef enum {
		INT32,
		UINT32,
		INT8,
		UINT8,
		INT16,
		UINT16,
		BOOLEAN,
		FLOAT,
		DOUBLE,
		STRING,
		CHAR,
		INT64,
		UINT64,
		VOID,

		CUSTOM
	} LanguageType;

	LanguageType type;
	std::string image;

	Type(LanguageType t)
	: 	SyntaxTreeNode("Type"), type(t) {
	}

	Type(char *_image)
	:	SyntaxTreeNode("Custom Type"), type(CUSTOM), image(_image) {

	}

};



#endif // PARSE_TYPE_H
