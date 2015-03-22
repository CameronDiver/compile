#include "lex.h"

#include <sstream>
#include <cctype>
#include <algorithm> 
#include <functional> 
#include <locale>

// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

inline void addIfNotEmpty(vector<Token> &tokens, string s, int lineno) {
	if(trim(s) != ""){
		Token t(s, lineno, "unknown");
		tokens.push_back(t);
	}
}

void lex(vector<Token> &tokens) {
	char c, lastC = ' ';
	stringstream ss("");
	bool inString = false, inComment = false;
	int lineno = 1;

	while((c = getNextChar()) != EOF) {
		if(inString) {
			// TODO: Handle escaping
			ss << c;
			while((c = getNextChar()) != '"' && c != EOF){
				ss << c;
				lastC = c;
			}
			
			ss << '"';
			
			addIfNotEmpty(tokens, ss.str(), lineno);
			ss.str("");

			inString = false;
		} else if(inComment) {
			// ignore everything on this line
			while((c = getNextChar()) != '\n' && c != EOF) ;
			inComment = false;

		} else {
			switch(c) {
				case '\n':
					++lineno;
					// intentional fall-through
				case ' ':
				case '\t':
				{			
					// create a new token, and add it to the
					// vector
					// FIXME: context
					addIfNotEmpty(tokens, ss.str(), lineno);
					ss.str("");
				}
				break;

				case '#':
				{
					inComment = true;
					addIfNotEmpty(tokens, ss.str(), lineno);
					ss.str("");
				}
				break;

				case '"':
				{
					inString = true;
					addIfNotEmpty(tokens, ss.str(), lineno);
					ss.str("");
					// initialising with a quote wasn't working
					ss << '"';
				}
				break;

				default:
					ss << c;
				break;
			}

			lastC = c;
		}
	}
	// There may be some data left in the stringstream
	addIfNotEmpty(tokens, ss.str(), lineno);
}
