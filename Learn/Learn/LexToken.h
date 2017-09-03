#pragma once

#include <string>
using namespace std;

class LexToken
{

private:
	string tokenType;
	string tokenValue;
public:
	LexToken(string raw);
	string getType();
	void printToken();

};