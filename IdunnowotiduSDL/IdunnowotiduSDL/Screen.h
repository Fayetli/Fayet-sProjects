#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#include "SDL.h"
#include <iostream>

namespace aye {

	class Screen
	{
	public:
		static const short int SCREEN_WIDTH = 800;
		static const short int SCREEN_HEIGHT = 400;
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		Uint32* buffer;
	public:
		void close();
		Screen();
		bool Init();
		void update();
	};

}
#endif // !SCREEN_H