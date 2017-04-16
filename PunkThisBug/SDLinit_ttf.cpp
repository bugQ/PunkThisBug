#include "SDLinit_ttf.h"
#include "SDLexception.h"


SDLinit_ttf::SDLinit_ttf()
{
	if (TTF_Init() < 0)
		throw SDLexception(TTF_GetError());
}


SDLinit_ttf::~SDLinit_ttf()
{
	TTF_Quit();
}
