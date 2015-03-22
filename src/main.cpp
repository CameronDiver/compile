#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "langconf.h"
#include "lex.h"
using namespace std;

FILE *src;

// TODO: support unicode
// Add this function here in case the source isn't always
// coming from a file
char getNextChar() {
	return fgetc(src);
}

int main(int argc, char *argv[]){
	printf("Language version %i.%i\n", Lang_VERSION_MAJOR, Lang_VERSION_MINOR);

	if(argc < 2) {
		printf("Usage: %s [source file]\n", argv[0]);
		return -1;
	}

	// attempt to open the file and pass it to the lexer
	src = fopen(argv[1], "r");
	if(src == NULL) {
		printf("Could not open input file %s\n", argv[1]);
	}
	
	// create a vector to hold the tokens
	vector<Token> tokens;
	lex(tokens);

	for(int x = 0; x < tokens.size(); ++x) {
		printf("Token: %s\n", tokens[x].getCData());
	}



    return 0;
}