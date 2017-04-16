//Using SDL and standard IO
#include "SDLinit.h"
#include "SDLinit_image.h"
#include "SDLinit_ttf.h"
#include "SDLwindow.h"
#include "SDLrenderer.h"
#include "SDLtexture.h"
#include "SDLfont.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	// init libraries
	SDLinit sdl(SDL_INIT_VIDEO);
	SDLinit_image sdl_img(IMG_INIT_PNG);
	SDLinit_ttf sdl_ttf;

	// create window and rendering context
	SDLwindow window("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDLrenderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDLfont oj("assets/orange juice 2.0.ttf", 72);
	SDLtexture hello(renderer, oj, "hello", SDL_Color{ 0, 0, 0 });
	SDL_Rect helloRect{ (SCREEN_WIDTH - hello.w) / 2, (SCREEN_HEIGHT - hello.h) / 2, hello.w, hello.h };

	renderer.set_draw_color(255, 255, 255, 255);
	renderer.clear();
	renderer.render(hello, NULL, &helloRect);
	renderer.update();

	SDL_Delay(2000);

	return 0;
}