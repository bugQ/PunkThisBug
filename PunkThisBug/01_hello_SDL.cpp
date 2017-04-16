//Using SDL and standard IO
#include "SDLinit.h"
#include "SDLinit_image.h"
#include "SDLwindow.h"
#include "SDLrenderer.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	SDLinit sdl(SDL_INIT_VIDEO);
	SDLinit_image sdl_img(IMG_INIT_PNG);

	SDLwindow window("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	SDLrenderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	renderer.set_draw_color(255, 255, 255, 255);
	renderer.clear();
	renderer.update();

	SDL_Delay(2000);

	return 0;
}