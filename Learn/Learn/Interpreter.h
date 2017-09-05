#pragma once
#include <string>
#include "Token.h"


class Interpreter
{
private:
	string text;
	int line;
	int position;
	Token currentToken;
	char currentChar;

	void advance();

public:
	Interpreter(string text);
	Token lex();
};