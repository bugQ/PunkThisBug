#pragma once
#include <SDL.h>

struct SDLrenderer;
struct SDLsurface;
struct SDLfont;

struct SDLtexture
{
	SDL_Texture * const ptr;
	const int w, h;

	SDLtexture(SDLrenderer & renderer, SDLsurface & surface);
	SDLtexture(SDLrenderer & renderer, const char * image_file);
	SDLtexture(SDLrenderer & renderer, SDLfont & font, const char * text, SDL_Color color);
	~SDLtexture();
};

