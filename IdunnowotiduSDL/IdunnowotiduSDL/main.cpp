#include "SDL.h"
#include "Screen.h"

using namespace aye;

int main(int argc, char** argv) {

	Screen screen;

	if (screen.Init())
		return 1;

	SDL_Event event;

	bool quit = false;
	while (!quit) {





		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				screen.close();
				quit = true;
			}
		}


	}











	return 0;
}