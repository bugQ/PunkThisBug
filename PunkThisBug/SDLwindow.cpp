#include "SDLwindow.h"
#include "SDLexception.h"
#include <SDL.h>


SDLwindow::SDLwindow(const char * title, int x, int y, int w, int h, Uint32 flags)
	: ptr(SDL_CreateWindow(title, x, y, w, h, flags))
{
	if (ptr == nullptr)
		throw SDLexception(SDL_GetError());
}


SDLwindow::~SDLwindow()
{
	SDL_DestroyWindow(ptr);
}

int SDLwindow::toggle_fullscreen()
{
	if (SDL_GetWindowFlags(ptr) & SDL_WINDOW_FULLSCREEN)
		return SDL_SetWindowFullscreen(ptr, 0);
	else
		return SDL_SetWindowFullscreen(ptr, SDL_WINDOW_FULLSCREEN);
}
