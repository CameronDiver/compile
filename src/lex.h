#ifndef LEX_H
#define LEX_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "token.h"

using namespace std;


// Get the next character of the src
extern char getNextChar();

void lex(vector<Token> &tokens);


#endif /* LEX_H */
