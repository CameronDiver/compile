#ifndef PARSE_STRING_H
#define PARSE_STRING_H

#include "node.h"

class String : public SyntaxTreeNode {
 public:
 	std::string image;
 	String(char *_image)
 	:	SyntaxTreeNode("String"), image(_image) {
 		// TODO: Escaping
 	};


 	std::string getStr() {
 		std::stringstream ss;
 		ss << "String " << image;
 		return ss.str();
 	}
};


#endif