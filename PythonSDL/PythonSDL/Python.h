#pragma once

#ifndef PYTHON_H
#define PYTHON_H

#include "Screen.h";
#include "Map.h"
#include <vector>

namespace aye {
	class Coord {
	public:
		int x;
		int y;
	};

	class Python
	{
	public:
		short int lastMove;
		int endX, endY;
		bool eat;
		std::vector<Coord> c;
	public:
		Python();
		void movePython();
		void setEndXY(int x, int y);
	};

}

#endif // !PYTHON_H

