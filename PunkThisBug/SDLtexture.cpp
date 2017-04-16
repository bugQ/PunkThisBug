#include "SDLtexture.h"
#include "SDLrenderer.h"
#include "SDLsurface.h"
#include "SDLexception.h"


SDLtexture::SDLtexture(SDLrenderer & renderer, SDLsurface & surface)
	: ptr(SDL_CreateTextureFromSurface(renderer.ptr, surface.ptr))
	, w(surface.ptr->w), h(surface.ptr->h)
{
	if (ptr == nullptr)
		throw SDLexception(SDL_GetError());
}

SDLtexture::SDLtexture(SDLrenderer & renderer, const char * image_file)
	: SDLtexture(renderer, SDLsurface(image_file))
{
}

SDLtexture::SDLtexture(SDLrenderer & renderer, SDLfont & font, const char * text, SDL_Color color)
	: SDLtexture(renderer, SDLsurface(font, text, color))
{
}

SDLtexture::~SDLtexture()
{
	SDL_DestroyTexture(ptr);
}
