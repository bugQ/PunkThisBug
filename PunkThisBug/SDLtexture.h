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

	bool set_blend_mode(SDL_BlendMode mode);
	bool set_color(Uint8 r, Uint8 g, Uint8 b);
	bool set_alpha(Uint8 alpha);
};

