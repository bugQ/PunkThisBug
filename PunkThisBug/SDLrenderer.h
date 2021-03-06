#pragma once
#include <SDL.h>

struct SDLwindow;
struct SDLtexture;

struct SDLrenderer
{
	SDL_Renderer * const ptr;

	SDLrenderer(SDLwindow & window, int index, Uint32 flags);
	~SDLrenderer();

	bool set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	bool clear();
	bool copy(SDLtexture & texture, SDL_Rect * src, SDL_Rect * dst, double angle = 0.0);
	void present();
};

