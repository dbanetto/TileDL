#include <unittest++/UnitTest++.h>
#include <SDL2/SDL.h>
#include "Game.h"

using namespace tiledl;

SUITE(GameTests)
{
	TEST(InitNoSDL) {
		Game gm;
		CHECK_EQUAL(-1, gm.init("", 1, 1, 0, -1, 0));
	}

	TEST(Init) {
		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			Game gm;
			CHECK_EQUAL(0, gm.init("", 1, 1, SDL_WINDOW_HIDDEN, -1, 0));
			SDL_Quit();
		} else {
			SDL_Log("Could not init SDL with SDL_INIT_VIDEO : %s", SDL_GetError());
		}
	}
}
