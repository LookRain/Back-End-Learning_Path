#include "stdafx.h"
#include "Interpreter.h"
#include "Token.h"

#include <string>
#include <vector>
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
const string NEWLINE = "NEWLINE";

const string INTEGER = "INTEGER";
const string NAME = "NAME";
const string VARIABLE = "VARIABLE";


const string PROCEDURE = "procedure";

const string EMPTY_TOKEN = "EMPTY TOKEN";

const int MAX_LENGTH = 1024;

const char NONE = '\0';
const char SPACE = ' ';
//const string PLUS, MINUS, MULTIPLY, DIVIDE, EQUAL = "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "EQUAL";


Interpreter :: Interpreter(string text) : text(text), currentToken(EMPTY_TOKEN, EMPTY_TOKEN)
{
	line = 1;
	//text = text;
	position = 0;
	currentChar = text[position]; 
	currentToken = Token(EMPTY_TOKEN, EMPTY_TOKEN);
	
	bufferPosition = 0;
}


Token Interpreter :: lex()
{
	Token null = Token("null", "null");
	int parenNum = 0; // ( )
	int braceNum = 0; // { }

	// 3 bool: {proc keyword found, starting brace found, ending brace found}
	bool procVerify[3] = {false, false, false};
	string currentProcName = "";


	while (currentChar != NONE)
	{
		// check if invalid var name
		if (bufferPosition != 0 && (isdigit(buffer[0])))
		{
			if (isalpha(buffer[bufferPosition - 1]))
			{
				cout << "invalid var name" << endl;
				return null;
			}
		}

		if (buffer[bufferPosition-1] == NONE) // if the current buffer array is a string
		{
			// keyword identification
			// case 1: procedure
			if (buffer == PROCEDURE)
			{
				if (procVerify[0])
				{
					cout << "cannot define procedure inside a procedure";
					return null;
				}
				procVerify[0] = true;
				cout << "procedure is detected" << endl;
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
			}

			
			currentProcName = buffer;
			cout << "proc name is " << currentProcName << endl;
			memset(buffer, 0, sizeof(buffer));
			bufferPosition = 0;
			
			

		}

		
		

		

		if (currentChar == SPACE)
		{
			buffer[bufferPosition] = '\0';
			
			bufferPosition++;

		} else
		{
			buffer[bufferPosition] = currentChar;
			bufferPosition++;
		}

		
		//cout << "buffer is: "<< buffer << " |||| " <<endl;
		advance();
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
