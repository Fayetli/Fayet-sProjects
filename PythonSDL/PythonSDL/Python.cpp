#include "Python.h"
#include <cstdlib>

namespace aye {


	Python::Python(){
		eat = NULL;
		lastMove = NULL;
		c.resize(c.size() + 1);
		c[0].x = 1 + rand() % (Screen::SCREEN_WIDTH / 10 - 3);
		c[0].y = 1 + rand() % (Screen::SCREEN_HEIGHT / 10 - 3);
		endX = c[0].x;
		endY = c[0].y;
	}
	void Python::setEndXY(int x, int y) {
		endX = x;
		endY = y;
	}
	void Python::movePython() {

		if (eat == 1) {
			for (int i = c.size() - 1; i > 0; i--) {
				c[i].x = c[i - 1].x;
				c[i].y = c[i - 1].y;
			}
		}
		else {
			for (int i = c.size() - 1; i > 0; i--) {
				c[i].x = c[i - 1].x;
				c[i].y = c[i - 1].y;
			}
		}
	}
	
}
