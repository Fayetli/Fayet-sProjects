#include "Screen.h"

namespace aye {

	Screen::Screen() {
		window = NULL;
		renderer = NULL;
		buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	}
	bool Screen::Init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			return 1;

		window = SDL_CreateWindow("What`s it??",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
			return 1;

		renderer = SDL_CreateRenderer(window, -1, 1);

		if (renderer == NULL)
			return 1;

		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

		if (texture == NULL)
			return 1;

		memset(buffer, NULL, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

		SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	void Screen::update() {
		SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	void Screen::close() {
		delete[] buffer;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
}