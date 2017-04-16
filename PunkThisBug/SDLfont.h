#pragma once
#include <SDL_ttf.h>

struct SDLfont
{
	TTF_Font * const ptr;

	SDLfont(const char * font_file, int points);
	~SDLfont();
};

