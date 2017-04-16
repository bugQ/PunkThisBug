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

bool SDLtexture::set_blend_mode(SDL_BlendMode mode)
{
	return !SDL_SetTextureBlendMode(ptr, mode);
}

bool SDLtexture::set_color(Uint8 r, Uint8 g, Uint8 b)
{
	return !SDL_SetTextureColorMod(ptr, r, g, b);
}

bool SDLtexture::set_alpha(Uint8 alpha)
{
	return !SDL_SetTextureAlphaMod(ptr, alpha);
}
