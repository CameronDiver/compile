#ifndef PARSE_LIST_H
#define PARSE_LIST_H

#include <cxxabi.h>

#include "node.h"

template<typename node>
class NodeList : public SyntaxTreeNode {
public:
	NodeList(std::string name, SyntaxTreeNode *item)
	: SyntaxTreeNode(name) {
		addChild(item);
	}

	NodeList(std::string name)
	: SyntaxTreeNode(name) {}

	int size(void) const {
		return children.size();
	}

	typename std::vector<node *>::iterator begin() {
		return children.begin();
	}

	typename std::vector<node *>::iterator end() {
		return children.end();
	}

	typename std::vector<node *>::const_iterator begin() const {
		return children.begin();
	}

	typename std::vector<node *>::const_iterator end() const {
		return children.end();
	} 

	// Accept a SyntaxTreeNode* and attempt to dynamic_cast it to
	// whatever node is
	node *addChild(SyntaxTreeNode *child) {
		if(child != NULL){
			node *elem = dynamic_cast<node *>(child);
			if(elem == NULL) {
				// TODO: throw exception
				
				std::cout << "Cast error: Attempted cast to " << typeid(node).name() << " but actual type was :" << child->getStr() << std::endl;
			}
			children.push_back(elem);
			return elem;
		}
		return child;
	}
};

#endif