#include "stdafx.h"
#include "NumToken.h"

NumToken::NumToken(string v) : Token(v)
{
	type = "N";
}



NumToken::~NumToken()
{
}
