#pragma once

#ifndef PYTHON_H
#define PYTHON_H

#include "Screen.h";
#include "Map.h"
#include <vector>

namespace aye {
	struct Coord {
	public:
		int x;
		int y;
	};

	class Python
	{
	public:
		short int ultimate;
		bool otherMove;
		float speedUp;
		short int speed;
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

