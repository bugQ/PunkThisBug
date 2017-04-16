#include "SDLinit_image.h"
#include "SDLexception.h"


SDLinit_image::SDLinit_image(Uint32 flags)
{
	if (!(IMG_Init(flags) & flags))
		throw SDLexception(IMG_GetError());
}


SDLinit_image::~SDLinit_image()
{
	IMG_Quit();
}
