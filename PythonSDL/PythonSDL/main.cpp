#include "SDL.h"
#include "Screen.h"
#include "Python.h"
#include "Map.h"
#include "GameManager.h"
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
	map.generateWalls();

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

		if (gm.event()) {
			break;
		}
		
		SDL_Delay(150);
	}

	std::cout << "Your score: " << python.c.size() - 1 << std::endl;
	return 0;
}