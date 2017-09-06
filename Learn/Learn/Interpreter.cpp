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

const string EOL = "EOL";
const string NEWLINE = "NEWLINE";

const string INTEGER = "INTEGER";
const string NAME = "NAME";
const string VARIABLE = "VARIABLE";


const string PROCEDURE = "procedure";

const string EMPTY_TOKEN = "EMPTY TOKEN";

const int MAX_LENGTH = 1024;

const char NONE = '\0';
const char LINE_FEED = '\n';
const char SPACE = ' ';
const string BLOCK_START = "{";
const string BLOCK_END = "}";
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

	string currentUnknownVar = "";

	string currentAssignVar = "";
	// 3 bool: {has var, has equal sign, has exp}
	bool assignVerify[3] = { false, false, false };

	// 3 bool: {proc keyword found, proc name defined, starting brace found, ending brace found}
	bool procVerify[4] = { false, false, false, false };
	string currentProcName = "";


	while (currentChar != NONE)
	{
		// check if invalid var name
		if (bufferPosition != 0 && (!isalpha(buffer[0])))
		{
			if (isalpha(buffer[bufferPosition - 1]))
			{
				cout << "invalid var name" << endl;
				return null;
			}
		}

		/*
		 * process parsed words here
		 */

		if (buffer[bufferPosition-1] == NONE) // if the current buffer array is a string
		{
			// keyword identification
			// case 1: procedure
			if (buffer == PROCEDURE)
			{
				// if alreaday expecting proc name
				if (procVerify[0])
				{
					cout << "cannot define procedure inside a procedure" << endl;
					return null;
				}
				procVerify[0] = true;
				cout << "procedure is detected" << endl;
				// reset buffer and continue
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
				continue;
			}

			// case 2: expecting proc name
			if (procVerify[0] && !procVerify[1])
			{
				currentProcName = buffer;
				procVerify[1] = true;
				cout << "proc name is " << currentProcName << endl;
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
				continue;
			}

			if (buffer == BLOCK_START)
			{
				if (procVerify[0] && procVerify[1])
				{
					cout << "proc block start" << endl;
					memset(buffer, 0, sizeof(buffer));
					bufferPosition = 0;			
				}
				continue;
			}
			if (!assignVerify[0])
			{
				/*cout << buffer << ", pointer: " << bufferPosition << endl;*/
				currentAssignVar = buffer;
				cout << "assignment variable is " << currentAssignVar << endl;
				assignVerify[0] = true;
				memset(buffer, 0, sizeof(buffer));
				bufferPosition = 0;
				continue;
			} else
			{
				cout << "invalid assignment syntax" << endl;
				return null;
			}
			
			
			
		}

		if (currentChar == SPACE || currentChar == LINE_FEED)
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
	for (int i = 0; i < 4; i ++)
	{
		cout << procVerify[i] << endl;
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
