#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "builtins.h"
#include "token.h"
#include "functiondef.h"
#include "ast.h"
#include "codegen/codegen.h"
#include "jit.h"

llvm::Module *module;
llvm::IRBuilder<> Builder(llvm::getGlobalContext());
std::map<std::string, llvm::Value*> NamedValues;

// A pointer to the function currently being built
FunctionDefinition *currentFn;
llvm::Function *currentFnllvm;

static std::map<std::string, BuiltinType> 	types;
static std::map<std::string, Keyword>		keywords;
static std::map<std::string, Operator>		operators;
static std::map<Operator, unsigned int>		precedence;
static std::map<std::string, UnaryOperator> unaryOperators;

static std::ifstream file;
static std::string filename;

void installTypes() {
	types.insert(std::pair<std::string, BuiltinType>("int", INTEGER));
	types.insert(std::pair<std::string, BuiltinType>("uint", UNSIGNED));
	types.insert(std::pair<std::string, BuiltinType>("int32", INTEGER));
	types.insert(std::pair<std::string, BuiltinType>("uint32", UNSIGNED));
	types.insert(std::pair<std::string, BuiltinType>("float", FLOAT));
	types.insert(std::pair<std::string, BuiltinType>("double", DOUBLE));
	types.insert(std::pair<std::string, BuiltinType>("int64", LONG_INTEGER));
	types.insert(std::pair<std::string, BuiltinType>("uint64", LONG_UNSIGNED));
	types.insert(std::pair<std::string, BuiltinType>("bool", BOOLEAN));


}

void installKeywords() {
	keywords.insert(std::pair<std::string, Keyword>("end", END));
	keywords.insert(std::pair<std::string, Keyword>("if", IF));
	keywords.insert(std::pair<std::string, Keyword>("else", ELSE));
	keywords.insert(std::pair<std::string, Keyword>("while", WHILE));
	keywords.insert(std::pair<std::string, Keyword>("extern", EXTERN));

}

void installOperators() {
	operators["+"] = PLUS;
	operators["-"] = MINUS;
	operators["*"] = MULT;
	operators["/"] = DIV;
	operators["="] = EQUALS;

	operators["<"] = LESSTHAN;
	operators[">"] = GREATTHAN;

	operators["!="] = NOTEQUALS;
	operators["%"] = MOD;
	operators["<="] = LESSTHANEQ;
	operators[">="] = GREATTHANEQ;

	operators["=="] = COMPARISON;

	operators["+="] = PLUSEQ;
	operators["-="] = MINUSEQ;
	operators["*="] = MULTEQ;
	operators["/="] = DIVEQ;

	operators["&"] = BITWISEAND;
	operators["&&"] = LOGICALAND;
 
}

void installUnaryOperators() {
	unaryOperators["!"] = LOGICALNOT;
	unaryOperators["~"] = BITWISENOT;
	// Don't set - to UNARYMINUS here,
	// because it is the same character as the 
	// binary minus it is handled specially
	//unaryOperators["-"] = UNARYMINUS;
	
}

void installPrecedence() {
	precedence[PLUS] = 20;
	precedence[MINUS] = 20;
	precedence[MULT] = 40;
	precedence[DIV] = 40;
	precedence[EQUALS] = 10;
	// TODO!!!!
}

BuiltinType typeLookup(std::string name) {
	if(types.find(name) == types.end())
		return TYPE_UNKNOWN;
	else 
		return types.at(name);
}

Keyword keywordLookup(std::string name) {
	// TODO: downcase the input
	if(keywords.find(name) == keywords.end())
		return NOT_KEYWORD;
	else
		return keywords.at(name);
}

Operator operatorLookup(std::string name) {
	if(operators.find(name) == operators.end())
		return NOT_OP;
	else
		return operators.at(name);
}

unsigned int precedenceLookup(Operator op) {
	if(precedence.find(op) == precedence.end()) {
		// This is an error, stop here
		return -1;
	}
	return precedence.at(op);
}

UnaryOperator unaryOperatorLookup(std::string data) {
	if(unaryOperators.find(data) == unaryOperators.end())
		return NOT_UNARY;
	return unaryOperators.at(data);
}

char getSourceChar() {
	return file.get();
}

std::string getTokenSource() {
	return filename;
}

int main(int argc, char *argv[]) {
	// intialisation
	installTypes();
	installKeywords();
	installOperators();
	installUnaryOperators();
	installPrecedence();


	if(argc < 2) {
		std::cout << "Error: Need input file" << std::endl;
		return -1;
	}

	filename = argv[1];

	// Open the file so that the tokeniser can read the characters
	file.open(filename.c_str(), std::ifstream::in);

	std::vector<Token> tokens;
	if(!Token::tokenize(tokens)) {
		std::cout << "Error: error tokenizing input" << std::endl;
		return -1;
	}

	// try to build the syntax tree
	AbstractSyntaxTree *tree = new AbstractSyntaxTree(tokens);

	// generate code
	currentFn = NULL;
	module = new llvm::Module("compiler", llvm::getGlobalContext());
	JITExecution *jit = new JITExecution();

	CodeGen *code = new CodeGen(tree);

	std::ofstream file("out.ll");
	llvm::raw_os_ostream stream(file);
	//llvm::WriteBitcodeToFile(Module, stream);
	module->print(stream, NULL);
	module->dump();

#if defined(DEBUG)
	std::cout << "Caling main function:" 
	<< "------------------------------------" << std::endl;
#endif	
	int ret = 	jit->callMain();
#if defined(DEBUG)
	std::cout << std::endl << "Returned value: " << ret << "\n";
#endif

	return ret;
}