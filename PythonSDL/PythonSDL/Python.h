#pragma once

#ifndef PYTHON_H
#define PYTHON_H

#include "Screen.h";
#include "Map.h"

namespace aye {

	class Python
	{
	public:
		short int lastMove;
		int endX, endY;
		int length;
		bool eat;
		int zone[(Screen::SCREEN_WIDTH / 10) * (Screen::SCREEN_HEIGHT / 10)][2];
	public:
		Python();
		void movePython();
		void setEndXY(int x, int y);
		bool checkMove();
	};

}

#endif // !PYTHON_H

