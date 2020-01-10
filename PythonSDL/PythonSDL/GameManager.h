#pragma once
#ifndef  GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Python.h"
#include "Map.h"
#include "Screen.h"

namespace aye {

	class GameManager
	{
	public:
		Python* python;
		Map* map;
		Screen* screen;
	public:
		GameManager(Python &python,Map &map, Screen &screen);
		void setEat();
		void checkEat();
		void printMap();
		void printPython();
		void printGrid();
		void movePython();
		bool checkMove();
		void session();
		bool event();
	};

}
#endif // ! GAMEMANAGER_H
