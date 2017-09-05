#include "stdafx.h"
#include "Interpreter.h"
#include "Token.h"

#include <string>
#include <iostream>

using namespace std;
// token types:
const string LETTER = "LETTER";
const string DIGIT = "DIGIT";
const string PLUS = "PLUS";
const string EQUAL = "EQUAL";
const string BLOCK_START = "BLOCK START";
const string BLOCK_END = "BLOCK END";
const string EOL = "EOL";
const string SPACE = "SPACE";
const string NEWLINE = "NEWLINE";

const string INTEGER = "INTEGER";
const string NAME = "NAME";

const string EMPTY_TOKEN = "EMPTY TOKEN";

const char NONE = '\0';

//const string PLUS, MINUS, MULTIPLY, DIVIDE, EQUAL = "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "EQUAL";


Interpreter :: Interpreter(string text) : text(text), currentToken(EMPTY_TOKEN, EMPTY_TOKEN)
{
	line = 1;
	//text = text;
	position = 0;
	currentChar = text[position]; 
	currentToken = Token(EMPTY_TOKEN, EMPTY_TOKEN);
}


Token Interpreter :: lex()
{
	Token null = Token("null", "null");

	while (currentChar != NONE)
	{
		if (isdigit(currentChar))
		{
			string st(1, currentChar);
			Token tk = Token("dummy", st);
			cout << tk.getValue();
			advance();
		}  else
		{
			advance();
		}
		
	}
	return null;
}

void Interpreter :: advance()
{
	position += 1;
	if (position > text.length() - 1)
	{
		currentChar = NONE;
	} else
	{
		currentChar = text[position];
	}
}
