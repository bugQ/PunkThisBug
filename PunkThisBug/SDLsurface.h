#pragma once
#include "SDLwindow.h"

struct SDLsurface
{
	SDLwindow & const window;
	SDL_Surface * const ptr;

	SDLsurface(SDLwindow & window);
	~SDLsurface();

	Uint32 mapRGB(Uint8 r, Uint8 g, Uint8 b);

	int clear(Uint32 color);
	int update();
};

