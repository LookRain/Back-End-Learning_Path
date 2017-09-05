// Learn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Token.h"
#include <string>
#include <iostream>
#include "Interpreter.h"

using namespace std;

void modifyInt(int a);
void modifyReal(int *a);

int main()
{


	int test = 1;
	cout << test << endl;
	cout << "after modifying" << endl;
	modifyInt(test);
	cout << test << endl;
	
	int test2 = 1;
	cout << test2 << endl;
	cout << "after modifying" << endl;
	modifyReal(&test2);
	cout << test2 << endl;


	Token myToken("keyword", "while");
	myToken.print();

	//string testStr = "hae11ha th22is is 33a te4st!  d";
	//cout << endl << isdigit(testStr[5]);

	Interpreter itp = Interpreter("hae11ha th22is is 33a te4st! \n d");
	itp.lex();

	
	return 0;
}


void modifyInt(int a) {
	a = 10;
}

void modifyReal(int *a)
{
	*a = 10;
}