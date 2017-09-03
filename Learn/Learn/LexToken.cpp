#include "stdafx.h"
#include "LexToken.h"

#include <string>
#include <iostream>
using namespace std;

LexToken :: LexToken(string raw)
{
	if (raw == "while")
	{
		this -> tokenType = "keyword";
		this-> tokenValue = raw;
	}
	
}

string LexToken::getType()
{
	return tokenType;
}

void LexToken::printToken()
{
	cout << "The Token is of type" << tokenType << " , of value " << tokenValue << endl;
}