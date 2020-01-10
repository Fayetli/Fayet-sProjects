#pragma once
#ifndef MAP_H
#define MAP_H

#include "Screen.h"
#include "Python.h"
#include <iostream>
#include <cstdlib>
namespace aye {

	class Map
	{
	public:
		int zone[Screen::SCREEN_WIDTH / 10][Screen::SCREEN_HEIGHT / 10];
	public:
		void generateWalls();
		Map();
	};

}
#endif // !MAP_H
