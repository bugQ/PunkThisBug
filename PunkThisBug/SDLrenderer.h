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
	bool render(SDLtexture & texture, SDL_Rect * src, SDL_Rect * dst);
	void update();
};

