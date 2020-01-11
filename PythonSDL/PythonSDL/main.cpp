#include "SDL.h"
#include "Screen.h"
#include "Python.h"
#include "Map.h"
#include "GameManager.h"
#include "Settings.h"
#include <cstdlib>
#include <ctime>

using namespace aye;

int main(int argv, char** argc) {

	srand(time(NULL));

	Screen screen;
	if (screen.init())
		return 1;

	Python python;
	
	Map map;
	map.generateWalls(wallsCount, python.c[0].x, python.c[0].y);
	map.generateHiddenEat(hiddenEatCount, python.c[0].x, python.c[0].y);


	GameManager gm(python, map, screen);
	gm.setEat();


	bool quit = false;

	while (true) {
	
		gm.session();

		if (gm.checkMove()) {
			SDL_Delay(500);
			screen.close();
			break;
		}

		screen.update();

		SDL_Delay(50);

		if (gm.event()) {
			break;
		}
		
		SDL_Delay((startSpeed - python.speed) * (1.0/python.speedUp));
	}

	return 0;
}