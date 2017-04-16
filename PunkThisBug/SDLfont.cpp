#include "SDLfont.h"
#include "SDLexception.h"


SDLfont::SDLfont(const char * font_file, int points)
	: ptr(TTF_OpenFont(font_file, points))
{
	if (ptr == nullptr)
		throw SDLexception(TTF_GetError());
}


SDLfont::~SDLfont()
{
	TTF_CloseFont(ptr);
}
