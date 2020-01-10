#include "Python.h"
#include <cstdlib>

namespace aye {


	Python::Python(){
		length = NULL;
		eat = NULL;
		lastMove = NULL;
		zone[0][0] = 1 + rand() % (Screen::SCREEN_WIDTH / 10 - 3);
		zone[0][1] = 1 + rand() % (Screen::SCREEN_HEIGHT / 10 - 3);
		endX = zone[0][0];
		endY = zone[0][1];
	}
	void Python::setEndXY(int x, int y) {
		endX = x;
		endY = y;
	}
	void Python::movePython() {

		if (eat == 1) {
			for (int i = length; i > 0; i--) {
				zone[i][0] = zone[i - 1][0];
				zone[i][1] = zone[i - 1][1];
			}
			zone[length - 1][0] = endX;
			zone[length - 1][1] = endY;
		}
		else {
			for (int i = length; i > 0; i--) {
				zone[i][0] = zone[i - 1][0];
				zone[i][1] = zone[i - 1][1];
			}
		}
	}
	bool Python::checkMove() {
		for (int i = 1; i <= length; i++) {
			if (zone[i][0] == zone[0][0] && zone[i][1] == zone[0][1])
				return 1;
		}
		if (zone[0][0] == 0 || zone[0][0] == Screen::SCREEN_WIDTH / 10 - 1 ||
			zone[0][1] == 0 || zone[0][1] == Screen::SCREEN_HEIGHT / 10 - 1)
			return 1;
		else return 0;
	}
}
