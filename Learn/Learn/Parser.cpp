#include "stdafx.h"
#include "Parser.h"
#include "Token.h"
#include "VarToken.h"
#include "OperatorToken.h"
#include "NumToken.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue> 
using namespace std;
// token types:


const string EOL = "EOL";
const string NEWLINE = "NEWLINE";

const string INTEGER = "INTEGER";
const string NAME = "NAME";
const string VARIABLE = "VARIABLE";


const string PROCEDURE = "procedure";

const string EMPTY_TOKEN = "EMPTY TOKEN";

const string EQUAL_STRING = "=";
const string PLUS_STRING = "+";
const string MINUS_STRING = "-";
const string MUL_STRING = "*";
const string SPACE_STRING = " ";
const string EMPTY_STRING = "";
const string LINE_FEED_STRING = "\n";
const string TAB_STRING = "\t";
const string SEMI_COLON_STRING = ";";
const string WHILE_STRING = "while";
const int MAX_LENGTH = 1024;

const char NONE = '\0';
const char LINE_FEED = '\n';
const char TAB = '\t';
const char SPACE = ' ';
const char SEMI_COLON = ';';
const char EQUAL = '=';
const char PLUS = '+';

const string BLOCK_START = "{";
const string BLOCK_END = "}";

enum type { proc_name, var_name, equal, plus, semi_colon, left_bracket, right_bracket, number };
string type_names[8] = { "procedure name", "variable name", "equal sign =", "plus sign +", "semi colon ;", "left bracket {", "right bracket }", "number" };
bool isLegalSymbol(char symbol)
{
	return (symbol == '{' || symbol == '}' || symbol == ';' || symbol == '+' || symbol == '=');
}
bool isIllegalSymbol(char symbol)
{
	if (!isalnum(symbol) && !isLegalSymbol(symbol) && symbol != SPACE && symbol != LINE_FEED && symbol != TAB)
	{
		
			cout << "illegal symbol is " << symbol << endl;

			return true;
		
	}
	return false;
	
}
bool isLegalName(string name)
{
	if (!isalpha(name[0]))
	{
		return false;
	}
	return true;
}
bool iskeyword(string word)
{
	if (word == "while")
	{
		return true;
	}
	return false;
}
void clearQueue(queue<Token> &q)
{
	queue<Token> empty;
	swap(q, empty);
}
bool Parser::match(type t)
{
	switch(t)
	{
	case proc_name:
		return (isLegalName(buffer));
	case var_name:
		return (isLegalName(buffer));
	case equal:
		return (buffer == EQUAL_STRING);
	case plus:
		return (buffer == PLUS_STRING);
	case semi_colon:
		return (buffer == SEMI_COLON_STRING);
	case left_bracket:
		return (buffer == BLOCK_START);
	case right_bracket:
		return (buffer == BLOCK_END);
	case number:
		return (isdigit(buffer[0]));
	}
	return false;
}
bool Parser::eat(string s)
{
	//cout << "buffer is ||" << buffer << "||, expect " << s << endl;
	bool ans = s == buffer;
	resetBuffer();
	getWord();
	return ans;
}
bool Parser::eat(type t)
{
	//cout << "buffer is ||" << buffer << "||, expect " << type_names[static_cast<int>(t)] << endl;
	bool ans = false;
	if (match(t))
	{
		ans = true;
	} else
	{
		cout << "Error while parsing: expect " << type_names[static_cast<int>(t)] << " but met " << buffer << " instead" << endl;
		exit(EXIT_FAILURE);
		//throw exception();
		return false;
	}
	resetBuffer();
	getWord();
	return ans;
}

Parser::Parser(string filename) : filename(filename), currentToken(EMPTY_TOKEN)
{
	ifstream ifs(filename);
	string content((istreambuf_iterator<char>(ifs)),
		(istreambuf_iterator<char>()));

	text = content;
	cout << text << endl;
	line = 1;
	//text = text;
	position = 0;
	currentChar = text[position];
	currentToken = Token(EMPTY_TOKEN);

	bufferPosition = 0;
}

void Parser::resetBuffer()
{
	memset(buffer, 0, sizeof(buffer));
	bufferPosition = 0;
}


int Parser::lex()
{
	if (isIllegalSymbol(currentChar))
	{
		/*cout << "illegal symbol " << currentChar << endl;*/

		return -1;
	}

	if (currentChar == SPACE)
	{
		//cout << "space! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;
		advance();
		return 1;
	}
	if (currentChar == LINE_FEED)
	{
		//cout << "linefeed! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;
		advance();
		return 1;
	}
	if (currentChar == TAB)
	{
		//cout << "linefeed! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;
		advance();
		return 1;
	}

	if (isLegalSymbol(currentChar))
	{
		if (isIllegalSymbol(text[position + 1]))
		{
			cout << "illegal symbol" << endl;
			return -1;
		}
		//cout << "symbol! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;
		buffer[bufferPosition] = currentChar;
		bufferPosition++;

		buffer[bufferPosition] = '\0';
		bufferPosition++;
		advance();
		return 1;
	}


	if (text[position + 1] == SPACE || text[position + 1] == TAB || text[position + 1] == LINE_FEED)
	{
		//cout << "next char is space! buffer is: " << buffer << " |||| position is " << position << "char is: " << currentChar << endl;

		buffer[bufferPosition] = currentChar;
		bufferPosition++;

		buffer[bufferPosition] = '\0';
		bufferPosition++;

		advance();
		return 1;
	}
	if (isLegalSymbol(text[position + 1]))
	{
		buffer[bufferPosition] = currentChar;
		bufferPosition++;

		buffer[bufferPosition] = '\0';
		bufferPosition++;

		advance();
		return 1;
	}

	if (isalnum(currentChar))
	{
		//cout << "buffer is: " << buffer << " |||| position is " << position << endl;
		buffer[bufferPosition] = currentChar;
		bufferPosition++;
		advance();
		return 1;
	}
	return -1;
}

int Parser::getWord()
{
	while (!buffer[bufferPosition - 1] == NONE)
	{
		int flag = lex();
		if (flag == -1)
		{
			exit(EXIT_FAILURE);
		}
		
	}
	//cout << buffer << endl;
	
	return 0;
}

bool Parser::parseProc()
{
	//cout << "buffer here " << buffer << endl;
	eat("procedure");
	//resetBuffer();

	eat(proc_name);
	eat(left_bracket);
	parseStmlst();
	eat(right_bracket);
	return true;
}

bool Parser::parseStmlst()
{
	parseStm();
	//cout << "buffer while parsing statement list is ||" << buffer << "||" << endl;
	if (buffer == BLOCK_END)
	{
		//cout << "end of block" << endl;
		return true;
	} else
	{
		parseStmlst();
	}
	
}

bool Parser::parseStm()
{
	string assignName = "";
	string controlVar = "";

	stack<Token> operatorStack;
	queue<Token> output;
	queue<Token> tokens;
	bool expectOperator = false;
	//cout << "buffer while parsing statement is ||" << buffer << "||" << endl;
	//cout << "point 1: " << buffer << endl;
	if (buffer != WHILE_STRING)
	{
		//cout << "Assignment detected!" << endl;

		assignName = buffer;
		eat(var_name);

		eat(equal);

		while (buffer != SEMI_COLON_STRING)
		{
			if (expectOperator)
			{
				operatorStack.push(OperatorToken(buffer));
				eat(plus);
				//cout << "operator is: " << PLUS_STRING << ". " << endl;
				
				expectOperator = false;

			}
			else
			{
				if (isdigit(buffer[0]))
				{
					//cout << "exp factor is a number: " << buffer << ". " << endl;
					output.push(NumToken(buffer));
					eat(number);
				}
				if (isalpha(buffer[0]))
				{
					//cout << "exp factor is a variable: " << buffer << ". " << endl;
					output.push(VarToken(buffer));
					eat(var_name);
				}

				expectOperator = true;
			}
		}

		while (!operatorStack.empty())
		{
			output.push(operatorStack.top());
			cout << "in stack:" << operatorStack.top().getValue() << endl;
			operatorStack.pop();
		}
		cout << "assignment of var " << assignName << " finished!" << endl;
		cout << "---------- start of output queue" << endl;
		while (!output.empty())
		{

			cout << output.front().getValue() << ", ";
			output.pop();
		}
		cout << '\n';
		clearQueue(output);
		cout << "-------------" << endl;

		eat(semi_colon);
		cout << "Assignment of var " << assignName << " ended" << endl;
	} else
	{
		eat("while");

		controlVar = buffer;
		eat(var_name);
		cout << "<<<< While statement with control var " << controlVar << " started >>>>>>>>" << endl;

		eat(left_bracket);
		parseStmlst();
		eat(right_bracket);
		cout << "<<<< While statement with control var " << controlVar << " ended" << endl;
	}
	
	return true;
}

void Parser::parse()
{
	Token null = Token("null");

	string currentUnknownVar = "";

	string currentAssignVar = "";
	bool assignExpectOp = false;
	// 3 bool: {has var, has equal sign, has exp}
	bool assignVerify[3] = { false, false, false };
	string leftFactor = "";
	string rightFactor = "";
	string op = "";
	int factorCount = 0;

	stack<Token> operatorStack;
	queue<Token> output;
	queue<Token> tokens;

	// 3 bool: {proc keyword found, proc name defined, starting brace found, ending brace found}
	bool procVerify[4] = { false, false, false, false };
	string currentProcName = "";

	// get initial word
	getWord();

	parseProc();

}

void Parser::advance()
{
	position += 1;
	if (position > text.length() - 1)
	{
		currentChar = NONE;
	}
	else
	{
		currentChar = text[position];
	}
}

