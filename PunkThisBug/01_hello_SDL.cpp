//Using SDL and standard IO
#include "SDLinit.h"
#include "SDLwindow.h"
#include "SDLsurface.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	SDLinit sdl(SDL_INIT_VIDEO);

	SDLwindow window("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	SDLsurface surface(window);

	surface.clear(surface.mapRGB(0xff, 0xff, 0xff));

	surface.update();

	SDL_Delay(2000);

	return 0;
}