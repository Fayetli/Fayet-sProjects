#include "Map.h"


namespace aye {

	Map::Map() {
		for (int x = 0; x < Screen::SCREEN_WIDTH / 10; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / 10; y++) {
				zone[x][y] = 0;
			}
		}
	}
	void Map::generateWalls() {
		for (int x = 0; x < Screen::SCREEN_WIDTH / 10; x++) {
			for (int y = 0; y < Screen::SCREEN_HEIGHT / 10; y++) {
				if (x == 0 || y == 0 || x == Screen::SCREEN_WIDTH / 10 - 1 || y == Screen::SCREEN_HEIGHT / 10 - 1)
					zone[x][y] = 1;
			}
		}
	}


}

