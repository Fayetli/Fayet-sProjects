#include "SDL.h"
#include "Screen.h"
#include "Map.h"
#include <iostream>
#include <iomanip>

namespace aye {

	Screen::Screen() {
		window = NULL;
		renderer = NULL;
		texture = NULL;
		buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	}
	bool Screen::init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			return 1;

		window = SDL_CreateWindow("Python",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
			return 1;

		renderer = SDL_CreateRenderer(window, -1, 1);

		if (renderer == NULL)
			return 1;

		texture = SDL_CreateTexture(renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
			SCREEN_WIDTH, SCREEN_HEIGHT);

		if (texture == NULL)
			return 1;

		memset(buffer, NULL, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(Uint32));

		SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		return false;
	}
	void Screen::update() {
		SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
	void Screen::printMap() {

		
	}
	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) return;

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		buffer[y * SCREEN_WIDTH + x] = color;
	}
	void Screen::close() {
		delete[] buffer;
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyTexture(texture);
		SDL_Quit();
	}

}