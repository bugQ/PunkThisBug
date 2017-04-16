#define SDL_MAIN_HANDLED

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
				frame = (frame + 1) % 8;
				src_rect.x = frame * w / 8;
			}
		}
	} monster(renderer, "assets/MONSTER-sheet.png");
	struct Maze : SDLtexture
	{
		// 8 x 4 tiles as bits
		Uint32 tile_bits = 0x3B7FF33Eu;
		SDLrenderer & renderer;
		
		// x, y relative to center
		bool collides(int x, int y)
		{
			x += w * 4; y += h * 2;
			if (x < 0 || y < 0)
				return false;
			x /= w; y /= h;
			if (x > 7 || y > 3)
				return false;
			int tile = x + y * 8;
			return tile_bits & (1 << tile);
		}

		void draw()
		{
			SDL_Rect dst;
			for (int i = 0; i < 32; ++i)
			{
				if (tile_bits & (1 << i))
				{
					dst = { SCREEN_W / 2 + (w * (i % 8 - 4)), SCREEN_H / 2 + (h * (i / 8 - 2)), w, h };
					renderer.copy(*this, nullptr, &dst);
				}
			}
		}

		Maze(SDLrenderer & renderer, const char * image_file)
			: SDLtexture(renderer, image_file), renderer(renderer)
		{
			set_blend_mode(SDL_BLENDMODE_NONE);
		}
	} maze(renderer, "assets/dirtCenter.png");
	struct Explorer : SDLtexture
	{
		int x = 0, y = 0;
		const int ycrop = 20;
		SDLrenderer & renderer;
		Maze & maze;

		void move(SDL_Keycode key)
		{
			switch (key)
			{
			case SDLK_LEFT:
				if (maze.collides(x - 1, y) && maze.collides(x - 1, y + h - ycrop))
					--x;
				break;
			case SDLK_RIGHT:
				if (maze.collides(x + w + 1, y) && maze.collides(x + w + 1, y + h - ycrop))
					++x;
				break;
			case SDLK_UP:
				if (maze.collides(x, y - 1) && maze.collides(x + w, y - 1))
					--y;
				break;
			case SDLK_DOWN:
				if (maze.collides(x, y + h - ycrop + 1) && maze.collides(x + w, y + h - ycrop + 1))
					++y;
				break;
			}
		}

		void draw()
		{
			SDL_Rect dst = {SCREEN_W / 2 + x, SCREEN_H / 2 + y, w, h};
			renderer.copy(*this, nullptr, &dst);
		}

		Explorer(SDLrenderer & renderer, SDLfont & font, Maze & maze)
			: SDLtexture(renderer, font, "X", {150, 150, 0})
			, renderer(renderer), maze(maze)
		{
			set_blend_mode(SDL_BLENDMODE_BLEND);
		}
	};

	// init text objects
	SDLfont oj("assets/orange juice 2.0.ttf", 72);
	SDLtexture texts[5] = {
		SDLtexture(renderer, oj, ">                                                              <", {150, 150, 150}),
		SDLtexture(renderer, oj, "Parallax Background Demo", {150, 0, 0}),
		SDLtexture(renderer, oj, "Sprite Animation Demo", {0, 150, 0}),
		SDLtexture(renderer, oj, "Grid Collision Demo", {0, 0, 150}),
		SDLtexture(renderer, oj, "Quit", {0, 0, 0}),
	};
	SDL_Rect text_rects[5];
	for (int i = 0; i < 5; ++i)
		text_rects[i] = { (SCREEN_W - texts[i].w) / 2, SCREEN_H * i / 5 - texts[i].h / 2, texts[i].w, texts[i].h };

	Explorer explorer(renderer, oj, maze);
	
	int scene = 0; // menu scene
	int selection = 1;

	while (scene < 4)
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
			maze.draw();
			explorer.draw();
			break;
		}

		renderer.present();

		SDL_Delay(16);
		
		// handle events
		SDL_Event event;
		int mouse_x, mouse_y;
		bool clicking;
		while (SDL_PollEvent(&event))
		{
			clicking = false;
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (SDL_BUTTON(SDL_BUTTON_LEFT))
					clicking = true;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_x, &mouse_y);
				if (mouse_x >= text_rects[0].x && mouse_x < text_rects[0].x + text_rects[0].w)
				{
					for (int i = 1; i <= 4; ++i)
					{
						if (mouse_y >= text_rects[i].y && mouse_y < text_rects[i].y + text_rects[i].h)
						{
							selection = i;
							if (clicking)
								scene = selection;
							break;
						}
					}
				}
				break;
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
					if (scene == 3)
						explorer.move(SDLK_DOWN);
					break;
				case SDLK_UP:
				case SDLK_k:
				case SDLK_w:
					if (scene == 0)
						selection = (selection + 2) % 4 + 1;
					if (scene == 3)
						explorer.move(SDLK_UP);
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
					if (scene == 3)
						explorer.move(SDLK_LEFT);
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
					if (scene == 3)
						explorer.move(SDLK_RIGHT);
					break;
				case SDLK_RETURN:
				case SDLK_SPACE:
				case SDLK_KP_ENTER:
					scene = selection;
				case SDLK_f:
					window.toggle_fullscreen();
					break;
				case SDLK_ESCAPE:
				case SDLK_q:
				case SDLK_BACKSPACE:
					if (scene == 0)
						scene = 4;
					else
						scene = 0;
				}
				break;
			case SDL_QUIT:
				scene = 4;
			}
		}
	}

	return 0;
}