#include "SDLwindow.h"
#include "SDLexception.h"
#include <SDL.h>


SDLwindow::SDLwindow(const char * title, int x, int y, int w, int h, Uint32 flags)
	: ptr(SDL_CreateWindow(title, x, y, w, h, flags))
{
	if (ptr == NULL)
	{
		throw SDLexception(SDL_GetError());
	}
}


SDLwindow::~SDLwindow()
{
	SDL_DestroyWindow(ptr);
}
