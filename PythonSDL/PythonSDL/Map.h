#pragma once
#ifndef MAP_H
#define MAP_H

#include "Screen.h"
#include "Python.h"
#include "Settings.h"

#include <iostream>
#include <cstdlib>
namespace aye {

	class Map
	{
	public:
		int zone[Screen::SCREEN_WIDTH / gridPixel][Screen::SCREEN_HEIGHT / gridPixel];
	public:
		void generateWalls(int wallsCount, int px, int py);
		void generateHiddenEat(int hiddenEatCount, int px, int py);
		Map();
	};

}
#endif // !MAP_H
