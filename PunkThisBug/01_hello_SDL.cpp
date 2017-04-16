#include "SDLinit.h"
#include "SDLinit_image.h"
#include "SDLinit_ttf.h"
#include "SDLwindow.h"
#include "SDLrenderer.h"
#include "SDLtexture.h"
#include "SDLfont.h"

const int SCREEN_W = 1280;
const int SCREEN_H = 720;

int main(int argc, char* args[])
{
	// init libraries
	SDLinit sdl(SDL_INIT_VIDEO);
	SDLinit_image sdl_img(IMG_INIT_PNG);
	SDLinit_ttf sdl_ttf;

	// create window and rendering context
	SDLwindow window("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	SDLrenderer renderer(window, 0, SDL_RENDERER_SOFTWARE);

	// init sprite objects
	struct ScrollingBG : SDLtexture {
		int pos = 0;
		SDLrenderer & renderer;

		ScrollingBG(SDLrenderer & renderer, const char * image_file)
			: SDLtexture(renderer, image_file), renderer(renderer)
		{
			set_blend_mode(SDL_BLENDMODE_BLEND);
		}
		void draw()
		{
			pos = (pos + w) % w;
			SDL_Rect src = {w-pos, 0, pos, h};
			SDL_Rect dst = {0, SCREEN_H - h, pos, h};
			renderer.copy(*this, &src, &dst);
			src.x = 0;  dst.x = pos;
			src.w = dst.w = w - pos;
			renderer.copy(*this, &src, &dst);
		}
	} bg1(renderer, "assets/parallax_bg1.png"), bg2(renderer, "assets/parallax_bg2.png");
	struct Monster : SDLtexture {
		bool animating;
		int frame = 0;
		double angle = 0.0;
		SDL_Rect src_rect, dst_rect;

		Monster(SDLrenderer & renderer, const char * image_file)
			: SDLtexture(renderer, image_file)
			, src_rect({ 0, 0, w / 8, h })
			, dst_rect({ (SCREEN_W - w / 8) / 2, (SCREEN_H - h) / 2, w / 8, h })
		{
			set_blend_mode(SDL_BLENDMODE_BLEND);
		}

		void advance_frame()
		{
			if (animating)
			{
				frame = (frame + 1) % 5;
				src_rect.x = frame * w / 8;
			}
		}
	} monster(renderer, "assets/MONSTER-sheet.png");

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
		text_rects[i] = { (SCREEN_W - texts[i].w) / 2, SCREEN_H * i / 5 - texts[i].h / 2, texts[i].w, texts[i].h };
	
	int scene = 0; // menu scene
	int selection = 1;

	bool quit = false;
	while (!quit)
	{
		// clear to white
		renderer.set_draw_color(255, 255, 255, 255);
		renderer.clear();

		// draw
		switch (scene)
		{
		case 0: // menu
			text_rects[0].y = text_rects[selection].y;
			for (int i = 0; i < 5; ++i)
				renderer.copy(texts[i], nullptr, &text_rects[i]);
			break;
		case 1: // parallax demo
			bg2.draw();
			bg1.draw();
			break;
		case 2: // animation demo
			renderer.copy(monster, &monster.src_rect, &monster.dst_rect, monster.angle);
			monster.advance_frame();
			break;
		case 3: // collision demo
			break;
		}

		renderer.present();

		SDL_Delay(16);

		// handle events
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_DOWN:
				case SDLK_j:
				case SDLK_s:
					if (scene == 0)
						selection = selection % 4 + 1;
					if (scene == 2)
						monster.animating = !monster.animating;
					break;
				case SDLK_UP:
				case SDLK_k:
				case SDLK_w:
					if (scene == 0)
						selection = (selection + 2) % 4 + 1;
					break;
				case SDLK_LEFT:
				case SDLK_h:
				case SDLK_a:
					if (scene == 1)
					{
						bg1.pos += 7;
						bg2.pos += 3;
					}
					if (scene == 2)
						monster.angle += 1;
					break;
				case SDLK_RIGHT:
				case SDLK_l:
				case SDLK_d:
					if (scene == 1)
					{
						bg1.pos -= 7;
						bg2.pos -= 3;
					}
					if (scene == 2)
						monster.angle -= 1;
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
				case SDLK_BACKSPACE:
					if (scene == 0)
						quit = true;
					else
						scene = 0;
				}
				break;
			case SDL_QUIT:
				quit = true;
			}
		}
	}

	return 0;
}