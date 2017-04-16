#pragma once
#include <SDL.h>

struct SDLwindow
{
	SDL_Window * const ptr;

	SDLwindow(const char * title, int x, int y, int w, int h, Uint32 flags);
	~SDLwindow();
};

