#include "SDLsurface.h"
#include "SDLwindow.h"
#include "SDLfont.h"
#include "SDLexception.h"

SDLsurface::SDLsurface(SDLwindow & window)
	: window(&window), ptr(SDL_GetWindowSurface(window.ptr))
{
	if (ptr == nullptr)
		throw SDLexception(SDL_GetError());
}

SDLsurface::SDLsurface(const char * image_file)
	: window(nullptr), ptr(IMG_Load(image_file))
{
	if (ptr == nullptr)
		throw SDLexception(IMG_GetError());
}

SDLsurface::SDLsurface(SDLfont & font, const char * text, SDL_Color color)
	: window(nullptr), ptr(TTF_RenderText_Solid(font.ptr, text, color))
{
	if (ptr == nullptr)
		throw SDLexception(TTF_GetError());
}

SDLsurface::~SDLsurface()
{
	if (window == nullptr)
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
	return SDL_UpdateWindowSurface(window->ptr);
}