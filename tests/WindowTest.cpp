#include <unittest++/UnitTest++.h>

#include "Window.h"

using namespace tiledl;

SUITE(WindowTests)
{
	TEST(ConstructorEmpty) {
		auto win = Window();
		CHECK(nullptr == win.getHandle());
		CHECK_EQUAL(true, win.isNull());
	}

	TEST(NoSDLInit) {
		auto win = Window();
		CHECK_EQUAL(false, win.init("", 0, 0, 1, 1, 0));
	}

	TEST(Init) {
		auto win = Window();

		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			CHECK(nullptr == win.getHandle());
			CHECK(win.init("", 0, 0, 1, 1, 0));
			CHECK(nullptr != win.getHandle() && NULL != win.getHandle());
			SDL_Quit();
		} else {
			SDL_Log("Could not init SDL with SDL_INIT_VIDEO : %s", SDL_GetError());
		}
	}
}
