#pragma once
#include <SDL_image.h>

struct SDLwindow;
struct SDLfont;

struct SDLsurface
{
	SDL_Surface * const ptr;

	// only used if it's a window surface.  nullptr otherwise
	SDLwindow * const window;

	SDLsurface(SDLwindow & window);
	SDLsurface(const char * image_file);
	SDLsurface(SDLfont & font, const char * text, SDL_Color color);
	~SDLsurface();

	Uint32 mapRGB(Uint8 r, Uint8 g, Uint8 b);

	int clear(Uint32 color);
	int update();
};

