#pragma once
#include <string>
#include <vector>
#include "Token.h"


class Parser
{
private:
	string filename;
	string text;
	int line;
	int position;
	Token currentToken;
	char currentChar;

	enum type { proc_name, var_name, equal, plus, semi_colon, left_bracket, right_bracket, number };

	char buffer[50];
	int bufferPosition;
	void advance();
	int lex();
	int getWord();
	void error(string e);
	void resetBuffer();
	bool match(type t);
	bool eat(type t);
	bool eat(string s);

	bool parseProc();
	bool parseStmlst();
	bool parseStm();

public:
	Parser(string filename);
	void parse();
};