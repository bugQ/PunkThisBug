#include "SDLrenderer.h"
#include "SDLwindow.h"
#include "SDLtexture.h"
#include "SDLexception.h"


SDLrenderer::SDLrenderer(SDLwindow & window, int index, Uint32 flags)
	: ptr(SDL_CreateRenderer(window.ptr, index, flags))
{
	if (ptr == nullptr)
		throw SDLexception(SDL_GetError());
}


SDLrenderer::~SDLrenderer()
{
	SDL_DestroyRenderer(ptr);
}

bool SDLrenderer::set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return !SDL_SetRenderDrawColor(ptr, r, g, b, a);
}

bool SDLrenderer::clear()
{
	return !SDL_RenderClear(ptr);
}

bool SDLrenderer::copy(SDLtexture & texture, SDL_Rect * src, SDL_Rect * dst)
{
	return !SDL_RenderCopy(ptr, texture.ptr, src, dst);
}

void SDLrenderer::present()
{
	SDL_RenderPresent(ptr);
}
