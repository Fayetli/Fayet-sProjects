#pragma once
#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"
#include <iostream>
#include "Settings.h"

namespace aye {

	class Screen
	{
	public:
		const static int SCREEN_WIDTH = screen_width;
		const static int SCREEN_HEIGHT = screen_height;
		Uint32* buffer;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
	public:
		Screen();
		bool init();
		void update();
		void printMap();
		void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void close();
	};

}
#endif // !SCREEN_H
