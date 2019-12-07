#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <thread>
#include <cstdlib>

using namespace std;

bool endGame = 1;

const int a = 12, b = 25;
int xEat = 0, yEat = 0;
int lastMove = 5, endX = 0, endY = 0;

//arrows
enum Moves { UP = 72, RIGHT = 77, DOWN = 80, LEFT = 75, Enter = 13 };

bool zone[a][b];
int python[(a - 2) * (b - 2)][2], length = 1;

void setXY(short x, short y)
{
	COORD coord = { y, x };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool checkWalls(int x, int y) {
	for (int i = 0; i < length; i++) {
		if (python[i][0] == x && python[i][1] == y)
			return 1;
	}
	if (x == 0 || x == a - 1 || y == 0 || y == b - 1)
		return 1;
	else return 0;
}

bool bsetEat = 1;
void setEat(int x, int y) {
	while (true) {
		bsetEat = 1;
		xEat = 1 + rand() % (a - 2);
		yEat = 1 + rand() % (b - 2);
		for (int i = 0; i < length; i++) {
			if (python[i][0] == xEat && python[i][1] == yEat) {
				bsetEat = 0;
			}
		}
		if (bsetEat == 1) {
			if (zone[xEat][yEat] == 0 && (x != xEat && y != yEat) ){
				setXY(xEat, yEat);
				cout << "0";
				setXY(x, y);
				break;
			}
		}
	}
}

bool eat = 0;
void checkEat(int x, int y) {
	eat = 0;
	if (x == xEat && y == yEat) {
		length++;
		setEat(x, y);
		eat = 1;
	}
}

void movePython() {
	
	if(eat == 1){
		for (int i = length - 1; i > 0; i--) {
			python[i][0] = python[i - 1][0];
			python[i][1] = python[i - 1][1];
		}
		python[length - 1][0] = endX;
		python[length - 1][1] = endY;
		for (int i = 1; i < length; i++) {
			setXY(python[i][0], python[i][1]);
			cout << "#";
		}
		setXY(endX, endY);
		cout << " ";
	}
	else {
		for (int i = length - 1; i > 0; i--) {
			python[i][0] = python[i - 1][0];
			python[i][1] = python[i - 1][1];
		}
		for (int i = 1; i < length; i++) {
			setXY(python[i][0], python[i][1]);
			cout << "#";
		}
		setXY(endX, endY);
		cout << " ";
	}
}

void setEndXY(int x, int y) {
	endX = x;
	endY = y;
}

void showScore(int x, int y) {
	setXY(a + 4, b + 2);
	cout << "Score:" << setw(3) << length - 1;
	setXY(x, y);
}

void showEndXY(int x, int y) {
	setXY(a + 5, b + 2);
	cout << "eX:" << setw(2) << endX << "eY:" << setw(3) << endY;
	setXY(x, y);
}

void showPythonCoord(int x, int y) {
	setXY(a + 6, 0);
	for (int i = 0; i < length; i++) {
		cout << "pX:" << setw(3) << python[i][0] << "pY:" << python[i][1] << endl;
	}
	setXY(x, y);
}

void showXY(short x, short y)
{
	setXY(a + 2, b + 2);
	cout << "X:" << setw(3) << x << " Y:" << setw(3) << y;
	setXY(x, y);
}

void showXYEat(int xEat, int yEat, int x, int y) {
	setXY(a + 3, b + 2);
	cout << "X:" << setw(3) << xEat << " Y:" << setw(3) << yEat;
	setXY(x, y);
}

void likeMove(int &x, int &y) {
	
	while (endGame) {
		switch (lastMove) {
		case 2:
			if (checkWalls(x - 1, y) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x - 1, y);
				movePython();
				setXY(--x, y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)193;
				Sleep(200);
			}
			else {
				lastMove = 0;
			}
			break;
		case 3:
			if (checkWalls(x + 1, y) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x + 1, y);
				movePython();
				setXY(++x, y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)194;
				Sleep(200);
			}
			else
				lastMove = 0;
			break;
		case 4:
			if (checkWalls(x, y + 1) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x, y + 1);
				movePython();
				setXY(x, ++y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)195;
				Sleep(200);
			}
			else
				lastMove = 0;
			break;
		case 1:
			if (checkWalls(x, y - 1) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x, y - 1);
				movePython();
				setXY(x, --y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)180;
				Sleep(200);
			}
			else
				lastMove = 0;
			break;
		case 0:
			setXY(a + 1, 0);
			endGame = 0;
			cout << "Good game!. Your score: " << length - 1;
			break;
		}
		setEndXY(python[length - 1][0], python[length - 1][1]);
		
	}
}

int main()
{
	srand(time(NULL));


	//buildWalls
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			if (i == 0 || i == a - 1 || j == 0 || j == b - 1)
				zone[i][j] = 1;
			else
				zone[i][j] = 0;
		}
	}

	//cout
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			setXY(i, j);
			if (zone[i][j] == 1)
				cout << "#";
		}
	}

	//set python
	int x = 0, y = 0;
	while (true) {
		x = 2 + rand() % a - 2;
		y = 2 + rand() % b - 2;
		if (zone[x][y] == 0)
			break;
	}
	setXY(x, y);
	cout << "#";
	python[0][0] = x;
	python[0][1] = y;

	

	//set Eat
	setEat(x, y);
	
	//thread
	thread move(likeMove, ref(x), ref(y));
	Sleep(2000);

	bool cont = true;
	
	while (endGame) {

		/*switch (_getch()) {
		case UP:
			if (checkWalls(x - 1, y) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x - 1, y);
				movePython();
				setXY(--x, y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)193;
				lastMove = 2;
			}
			else setXY(x, y);
			break;
		case DOWN:
			if (checkWalls(x + 1, y) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x + 1, y);
				movePython();
				setXY(++x, y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)194;
				lastMove = 3;
			}
			else setXY(x, y);
			break;
		case RIGHT:
			if (checkWalls(x, y + 1) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x, y + 1);
				movePython();
				setXY(x, ++y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)195;
				lastMove = 4;
			}
			else setXY(x, y);
			break;
		case LEFT:
			if (checkWalls(x, y - 1) == 0) {
				setXY(x, y);
				cout << " ";
				checkEat(x, y - 1);
				movePython();
				setXY(x, --y);
				python[0][0] = x;
				python[0][1] = y;
				cout << (char)180;
				lastMove = 1;
			}
			else setXY(x, y);
			break;
		case Enter:
			cont = 0;
			break;
		}
		setEndXY(python[length - 1][0], python[length - 1][1]);
		showEndXY(x, y);
		showScore(x, y);
		showXY(x, y);
		showXYEat(xEat, yEat, x, y);*/
		switch (_getch()) {
		case UP:
			if(lastMove != 3)
			lastMove = 2;
			Sleep(200);
			break;
		case DOWN:
			if (lastMove != 2)
			lastMove = 3;
			Sleep(200);
			break;
		case RIGHT:
			if (lastMove != 1)
			lastMove = 4;
			Sleep(200);
			break;
		case LEFT:
			if (lastMove != 4)
			lastMove = 1;
			Sleep(200);
			break;
		case Enter:
			lastMove = 0;
			break;
		}
	}




}
