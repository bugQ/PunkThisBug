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

	// init text objects
	SDLfont oj("assets/orange juice 2.0.ttf", 72);
	SDLtexture texts[5] = {
		SDLtexture(renderer, oj, ">                   <", {150, 150, 150}),
		SDLtexture(renderer, oj, "Scene 1", {150, 0, 0}),
		SDLtexture(renderer, oj, "Scene 2", {0, 150, 0}),
		SDLtexture(renderer, oj, "Scene 3", {0, 0, 150}),
		SDLtexture(renderer, oj, "Quit", {0, 0, 0}),
	};
	SDL_Rect text_rects[5];
	for (int i = 0; i < 5; ++i)
		text_rects[i] = { (SCREEN_WIDTH - texts[i].w) / 2, SCREEN_HEIGHT * i / 5 - texts[i].h / 2, texts[i].w, texts[i].h };
	
	int scene = 0; // menu scene
	int selection = 1;

	bool quit = false;
	while (!quit)
	{
		renderer.set_draw_color(255, 255, 255, 255);
		renderer.clear();
		
		switch (scene)
		{
		case 0: // menu
			text_rects[0].y = text_rects[selection].y;
			for (int i = 0; i < 5; ++i)
				renderer.copy(texts[i], nullptr, &text_rects[i]);
		}

		renderer.present();

		SDL_Delay(16);

		// handle events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true; break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_DOWN:
				case SDLK_j:
				case SDLK_s:
					if (scene == 0)
						selection = selection % 4 + 1;
					break;
				case SDLK_UP:
				case SDLK_k:
				case SDLK_w:
					if (scene == 0)
						selection = (selection + 2) % 4 + 1;
					break;
				case SDLK_RETURN:
				case SDLK_SPACE:
				case SDLK_KP_ENTER:
					switch (selection)
					{
					case 1:
					case 2:
					case 3:
						scene = selection;
						break;
					case 4:
					default:
						quit = true;
					}
					break;
				case SDLK_ESCAPE:
				case SDLK_q:
					if (scene == 0)
						quit = true;
					else
						scene = 0;
				}
				break;
			}
		}
	}

	return 0;
}