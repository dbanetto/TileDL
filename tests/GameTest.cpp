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
		SDL_Init(SDL_INIT_VIDEO);
		Game gm;
		CHECK_EQUAL(0, gm.init("", 1, 1, SDL_WINDOW_HIDDEN, -1, 0));
		SDL_Quit();
	}
}
