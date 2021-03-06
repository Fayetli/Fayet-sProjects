#include "GameManager.h"
#include "Settings.h"

namespace aye {
	GameManager::GameManager(Python& python, Map& map, Screen& screen) {
		this->python = &python;
		this->map = &map;
		this->screen = &screen;
	}
	void GameManager::setEat() {
		bool quit1 = false;
		int eatx, eaty;
		while (!quit1) {
			eatx = 1 + rand() % (Screen::SCREEN_WIDTH / gridPixel - 3);
			eaty = 1 + rand() % (Screen::SCREEN_HEIGHT / gridPixel - 3);	
			quit1 = true;
			for (int i = 0; i < (*python).c.size(); i++) {
				if (((*python).c[i].x == eatx && (*python).c[i].y == eaty)||
					(*map).zone[eatx][eaty] == 1) {
						quit1 = false;
						break;
				}
			}
		}
		(*map).zone[eatx][eaty] = 2;
	}
	void GameManager::checkEat() {
		(*python).eat = 0;
		if ((*map).zone[(*python).c[0].x][(*python).c[0].y] == 2) {//walls
			if ((*python).speed - startUnSpeed > pythonSpeedUp)
				(*python).speed += pythonSpeedUp;
			(*python).c.resize((*python).c.size() + 1);
			(*python).eat = 1;
			int x = (*python).c[0].x;
			int y = (*python).c[0].y;
			(*map).zone[x][y] = 0;
			setEat();
			if ((*python).c.size() % giveUltimate - 1 == 0 && (*python).ultimate < 3)//give ulrimate
				(*python).ultimate = (*python).ultimate + 1;
		}


	}
	void GameManager::printMap() {
		for (int x = 0; x < Screen::SCREEN_WIDTH / gridPixel; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / gridPixel; y++) {
				if ((*map).zone[x][y] == 1 || (*map).zone[x][y] == 3 ){
					for (int i = 1; i < gridPixel; i++) {
						for (int j = 1; j < gridPixel; j++) {
							(*screen).setPixel(x * gridPixel + i, y * gridPixel + j, 0, 255, 0);//walls
						}
					}
				}
				if ((*map).zone[x][y] == 2) {
					for (int i = 1; i < gridPixel; i++) {
						for (int j = 1; j < gridPixel; j++) {
							(*screen).setPixel(x * gridPixel + i, y * gridPixel + j, 255, 0, 0);//eat
						}
					}
				}
			}
		}
	}
	void GameManager::printPython() {
		Uint8 red = 0, green = 0, blue = 0;
		if ((*python).ultimate == 1) {
			green = 0xFF;
			red = 0xFF;
		}
		if ((*python).ultimate == 2) {
			blue = 0xFF;
			red = 0xFF;
		}
		if ((*python).ultimate == 3) {
			blue = 0xFF;
			green = 0xFF;
		}
		for (int x = 0; x < Screen::SCREEN_WIDTH / gridPixel; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / gridPixel; y++) {
				if (x == (*python).c[0].x && y == (*python).c[0].y) {
					for (int i = 1; i < gridPixel; i++) {
						for (int j = 1; j < gridPixel; j++) {
							if(i == 1 || j == 1 || i == gridPixel - 1 || j == gridPixel - 1)
								(*screen).setPixel(x * gridPixel + i, y * gridPixel + j, 255, 255, 255);//around head og python 
							else
								(*screen).setPixel(x * gridPixel + i, y * gridPixel + j, red, green, blue);//head Of Python
						}
					}
				}
				for (int l = 1; l < (*python).c.size(); l++) {
					if (x == (*python).c[l].x && y == (*python).c[l].y) {
						for (int i = 2; i < gridPixel - 1; i++) {
							for (int j = 2; j < gridPixel - 1; j++) {
								(*screen).setPixel(x * gridPixel + i, y * gridPixel + j, 0, 0, 255);//python
							}
						}
					}
				}
			}
		}
	}
	void GameManager::printGrid() {
		for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
				if (!(x % gridPixel == 0 || y % gridPixel == 0)) {
					(*screen).setPixel(x, y, 255, 255, 255);//background
				}
			}
		}
	}
	void GameManager::movePython() {
		if (!(*python).otherMove) {
			(*python).speedUp += oneLineSpeedUp;
		}
		else (*python).speedUp = 1;
		(*python).otherMove = 0;
		switch ((*python).lastMove) {
		case 1:
			(*python).movePython();
			(*python).c[0].x = (*python).c[0].x - 1;
			(*python).c[0].y = (*python).c[0].y;
			break;
		case 2:
			(*python).movePython();
			(*python).c[0].x = (*python).c[0].x;
			(*python).c[0].y = (*python).c[0].y - 1;
			break;
		case 3:
			(*python).movePython();
			(*python).c[0].x = (*python).c[0].x;
			(*python).c[0].y = (*python).c[0].y + 1;
			break;
		case 4:
			(*python).movePython();
			(*python).c[0].x = (*python).c[0].x + 1;
			(*python).c[0].y = (*python).c[0].y;
			break;
		default:
			break;
		}
		(*python).setEndXY((*python).c[(*python).c.size() - 1].x, (*python).c[(*python).c.size() - 1].y);
	}
	bool GameManager::checkMove() {
		for (int i = 1; i < (*python).c.size(); i++) {
			if ((*python).c[i].x == (*python).c[0].x && (*python).c[i].y == (*python).c[0].y)
				return true;
		}
		int x = (*python).c[0].x;
		int y = (*python).c[0].y;
		if ((*map).zone[x][y] == 1) {
			if ((*python).ultimate != 0) {
				(*map).zone[x][y] = 0;
				(*python).ultimate = (*python).ultimate - 1;
				return false;
			}
			else
				return true;
		}
		else if ((*map).zone[x][y] == 3) {
			return true;
		}
		else return false;
	}
	void GameManager::session() {
		movePython();
		printGrid();
		printMap();
		printPython();
		checkEat();
	}
	bool GameManager::event(){
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return true;
			else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					if((*python).lastMove != 1)
						(*python).otherMove = true;
					if ((*python).c.size() == 1 || (*python).lastMove != 4)
						(*python).lastMove = 1;
					return false;
				case SDLK_UP:
					if ((*python).lastMove != 2)
						(*python).otherMove = true;
					if ((*python).c.size() == 1 || (*python).lastMove != 3)
						(*python).lastMove = 2;
					return false;
				case SDLK_DOWN:
					if ((*python).lastMove != 3)
						(*python).otherMove = true;
					if ((*python).c.size() == 1 || (*python).lastMove != 2)
						(*python).lastMove = 3;
					return false;
				case SDLK_RIGHT:
					if ((*python).lastMove != 4)
						(*python).otherMove = true;
					if ((*python).c.size() == 1 || (*python).lastMove != 1)
						(*python).lastMove = 4;
					return false;
				default:
					return false;
				}
			}
		}
	}
}