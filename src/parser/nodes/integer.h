#ifndef PARSE_INTEGER_H
#define PARSE_INTEGER_H

#include <cstdint>
#include <string>
#include <sstream>

#include "node.h"

class Integer : public SyntaxTreeNode {
 public:
 	uint64_t value;
 	Integer(char *image, int base=10)
 	:	SyntaxTreeNode("Integer") {
 		// Get number from image
 		value = intFromImage(image);
 	};


 	int intFromImage(char *image) {
 		return atoi(image);
 	}

 	std::string getStr() {
 		std::stringstream ss;
 		ss << "Integer: ";
 		ss << value;
 		return ss.str();
 	}
};


#endif