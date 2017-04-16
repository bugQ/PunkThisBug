#include "SDLinit.h"
#include "SDLexception.h"
#include <cstdio>


SDLinit::SDLinit(Uint32 flags)
{
	if (SDL_Init(flags) < 0)
		throw SDLexception(SDL_GetError());
}


SDLinit::~SDLinit()
{
	SDL_Quit();
}
