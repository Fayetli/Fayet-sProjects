#include "SDL.h"
#include "Screen.h"
#include "Python.h"
#include "Map.h"
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
	///////////////////////setEat/////////////////////
	{
		bool quit = false;
		int x, y;
		while (!quit) {
			x = 1 + rand() % (Screen::SCREEN_WIDTH / 10 - 3);
			y = 1 + rand() % (Screen::SCREEN_HEIGHT / 10 - 3);
			quit = true;
			for (int i = 0; i <= python.length; i++) {
				if (python.zone[i][0] == x && python.zone[i][1] == y) {
					quit = false;
					break;
				}
			}
		}
		map.zone[x][y] = 2;
	}
	
	SDL_Event event;



	bool quit = false;

	while (!quit) {
		if (python.checkMove()) {
			SDL_Delay(1000);
			screen.close();
			break;
		}
		switch (python.lastMove) {
		case 1:
			python.movePython();
			python.zone[0][0] = python.zone[0][0] - 1;
			python.zone[0][1] = python.zone[0][1];
			break;
		case 2:
			python.movePython();
			python.zone[0][0] = python.zone[0][0];
			python.zone[0][1] = python.zone[0][1] - 1;
			break;
		case 3:
			python.movePython();
			python.zone[0][0] = python.zone[0][0];
			python.zone[0][1] = python.zone[0][1] + 1;
			break;
		case 4:
			python.movePython();
			python.zone[0][0] = python.zone[0][0] + 1;
			python.zone[0][1] = python.zone[0][1];
			break;
		default:
			break;
		}
		python.setEndXY(python.zone[python.length][0], python.zone[python.length][1]);


		//////////////////////checkEat/////////////////////
		python.eat = 0;
		if (map.zone[python.zone[0][0]][python.zone[0][1]] == 2) {
			python.length = python.length + 1;
			python.eat = 1;
			map.zone[python.zone[0][0]][python.zone[0][1]] = 0;
			///////////////////////setEat///////////////
			{
				bool quit1 = false;
				int eatx, eaty;
				while (!quit1) {
					eatx = 1 + rand() % (Screen::SCREEN_WIDTH / 10 - 3);
					eaty = 1 + rand() % (Screen::SCREEN_HEIGHT / 10 - 3);
					quit1 = true;
					for (int i = 0; i <= python.length; i++) {
						if (python.zone[i][0] == eatx && python.zone[i][1] == eaty) {
							quit1 = false;
							break;
						}
					}
				}
				map.zone[eatx][eaty] = 2;
			}
		}
		/////////////////////printGrid////////////////
		for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				if (!(x % 10 == 0 || y % 10 == 0)) {
					screen.setPixel(x, y, 255, 255, 255);
				}
			}
		}
		/////////////////printMap//////////////////////
		for (int x = 0; x < Screen::SCREEN_WIDTH / 10; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / 10; y++) {
				if (map.zone[x][y] == 1) {
					for (int i = 1; i < 10; i++) {
						for (int j = 1; j < 10; j++) {
							screen.setPixel(x*10 + i, y*10 + j, 0, 255, 0);
						}
					}
				}
				if (map.zone[x][y] == 2) {
					for (int i = 1; i < 10; i++) {
						for (int j = 1; j < 10; j++) {
							screen.setPixel(x * 10 + i, y * 10 + j, 255, 0, 0);
						}
					}
				}
			}
		}
		/////////////////////printPython////////////////////
		for (int x = 0; x < Screen::SCREEN_WIDTH / 10; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / 10; y++) {
				if (x == python.zone[0][0] && y == python.zone[0][1]) {
					for (int i = 2; i < 9; i++) {
						for (int j = 2; j < 9; j++) {
							screen.setPixel(x * 10 + i, y * 10 + j, 0, 0, 0);
						}
					}
				}
				for (int l = 1; l <= python.length; l++) {
					if (x == python.zone[l][0] && y == python.zone[l][1]) {
						for (int i = 2; i < 9; i++) {
							for (int j = 2; j < 9; j++) {
								screen.setPixel(x * 10 + i, y * 10 + j, 0, 0, 255);
							}
						}
					}
				}
			}
		}


		screen.update();

		//////////////////////////////////////userChoose////////////////////////////////////////////
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					python.lastMove = 1;
					break;
				case SDLK_UP:
					python.lastMove = 2;
					break;
				case SDLK_DOWN:
					python.lastMove = 3;
					break;
				case SDLK_RIGHT:
					python.lastMove = 4;
					break;
				}
				break;
			}
		}
		
		////////////////////movePython//////////////////
		SDL_Delay(200);
	}
	std::cout << "Your score: " << python.length << std::endl;
	return 0;
}