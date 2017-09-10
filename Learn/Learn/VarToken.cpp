#include "stdafx.h"
#include "VarToken.h"


VarToken::VarToken(string v) : Token(v)
{
	type = "V";
}


VarToken::~VarToken()
{
}
