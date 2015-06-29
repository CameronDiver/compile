#ifndef PARSE_FLOAT_H
#define PARSE_FLOAT_H

#include <string>
#include <sstream>

#include "node.h"

class Float : public SyntaxTreeNode {
 public:
 	double value;
 	Float(char *image)
 	:	SyntaxTreeNode("Float") {
 		value = floatFromImage(image);
 	};

 	double floatFromImage(char *image) {
 		return atof(image);
 	}

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Float: " << value;
 		return ss.str();
 	}
};



#endif