#include "SDLsurface.h"
#include "SDLexception.h"


SDLsurface::SDLsurface(SDLwindow & window)
	: window(window), ptr(SDL_GetWindowSurface(window.ptr))
{
	if (ptr == NULL)
	{
		throw SDLexception(SDL_GetError());
	}
}


SDLsurface::~SDLsurface()
{
	SDL_FreeSurface(ptr);
}

Uint32 SDLsurface::mapRGB(Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB(ptr->format, r, g, b);
}

int SDLsurface::clear(Uint32 color)
{
	return SDL_FillRect(ptr, NULL, color);
}

int SDLsurface::update()
{
	return SDL_UpdateWindowSurface(window.ptr);
}