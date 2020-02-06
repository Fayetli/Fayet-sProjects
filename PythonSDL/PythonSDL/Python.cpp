#include "Python.h"
#include <cstdlib>
#include "Settings.h"

namespace aye {


	Python::Python(){
		ultimate = startUltimatesCount;
		speed = NULL;
		speedUp = 1;
		eat = NULL;
		lastMove = NULL;
		otherMove = NULL;
		c.resize(c.size() + 1);
		c[0].x = 1 + rand() % (Screen::SCREEN_WIDTH / gridPixel - 3);
		c[0].y = 1 + rand() % (Screen::SCREEN_HEIGHT / gridPixel - 3);
		endX = c[0].x;
		endY = c[0].y;
	}
	void Python::setEndXY(int x, int y) {
		endX = x;
		endY = y;
	}
	void Python::movePython() {

		for (int i = c.size() - 1; i > 0; i--) {
			c[i].x = c[i - 1].x;
			c[i].y = c[i - 1].y;
		}

		
	}
	
}
