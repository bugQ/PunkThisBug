#pragma once
#include <SDL.h>

struct SDLrenderer;
struct SDLsurface;

struct SDLtexture
{
	SDL_Texture * const ptr;

	SDLtexture(SDLrenderer & renderer, SDLsurface & surface);
	SDLtexture(SDLrenderer & renderer, const char * image_file);
	~SDLtexture();
};

