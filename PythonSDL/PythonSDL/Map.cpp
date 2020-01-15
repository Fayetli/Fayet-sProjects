#include "Map.h"


namespace aye {

	Map::Map() {
		for (int x = 0; x < Screen::SCREEN_WIDTH / gridPixel; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / gridPixel; y++) {
				zone[x][y] = 0;//init
			}
		}
	}
	void Map::generateWalls(int wallsCount, int px, int py) {
		for (int x = 0; x < Screen::SCREEN_WIDTH / gridPixel; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / gridPixel; y++) {
				if (x == 0 || y == 0 || x == Screen::SCREEN_WIDTH / gridPixel - 1 || y == Screen::SCREEN_HEIGHT / gridPixel - 1)
					zone[x][y] = 3;//unbreakble walls
			}
		}
		while (wallsCount) {//breakble walls
			int x = 2 + rand() % (Screen::SCREEN_WIDTH / gridPixel - 5);
			int y = 2 + rand() % (Screen::SCREEN_HEIGHT / gridPixel - 5);
			bool goWall = 1;
			switch (rand() % 2) {
			case 0:
				for (int i = -2; i <= 2; i++) {
					for (int j = -1; j <= 1; j++) {
						if (zone[x + i][y + j] == 1 || (x + i == px || y + j == py)) {
							goWall = 0;
							break;
						}
					}
				}
				if (goWall) {
					zone[x][y] = zone[x + 1][y] = zone[x - 1][y] = 1;
					wallsCount--;
				}
				break;
			case 1:
				for (int i = -2; i <= 2; i++) {
					for (int j = -1; j <= 1; j++) {
						if (zone[x + j][y + i] == 1 || (x + j == px && x + i == py)) {
							goWall = 0;
							break;
						}
					}
					if (!goWall)
						break;
				}
				if (goWall) {
					zone[x][y] = zone[x][y + 1] = zone[x][y - 1] = 1;
					wallsCount--;
				}
				break;
			}
		}
	}
	void Map::generateHiddenEat(int hiddenEatCount, int px, int py) {
		while (hiddenEatCount) {
			int x = 2 + rand() % (Screen::SCREEN_WIDTH / gridPixel - 5);
			int y = 2 + rand() % (Screen::SCREEN_HEIGHT / gridPixel - 5);
			bool goEat = 1;
			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {
					if (zone[x + j][y + i] == 1 || (x + j == px && x + i == py)) {
						goEat = 0;
						break;
					}
				}
				if (!goEat)
					break;
			}
			if (goEat) {
				for (int i = -1; i <= 1; i++) {
					for (int j = -1; j <= 1; j++) {
						if (i == 0 && j == 0)
							continue;
						zone[x + i][y + j] = 1;
					}
				}
				zone[x][y] = 2;
				hiddenEatCount--;
			}
		}
	}

}

