#include <unittest++/UnitTest++.h>

#include "Renderer.h"
#include <stdexcept>

using namespace tiledl;

SUITE(RendererTests)
{
	TEST(ConstructorEmpty) {
		auto renderer = Renderer();
		CHECK(nullptr == renderer.getHandle());
		CHECK_EQUAL(true, renderer.isNull());
	}

	TEST(ConstructorNull) {
		CHECK_THROW(Renderer(nullptr, 0, 0), std::runtime_error);
	}

	TEST(NoSDLInit) {
		auto renderer = Renderer();
		CHECK_EQUAL(false, renderer.init(nullptr, -1, 0));
	}

	TEST(WithSDLBadInit) {
		auto renderer = Renderer();

		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			CHECK_EQUAL(false, renderer.init(nullptr, -1, 0));
			SDL_Quit();
		} else {
			SDL_Log("Could not init SDL with SDL_INIT_VIDEO : %s", SDL_GetError());
		}
	}

	TEST(WithSDLBadInitSW) {
		auto renderer = Renderer();

		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			CHECK_EQUAL(false, renderer.initSW(nullptr));
			SDL_Quit();
		} else {
			SDL_Log("Could not init SDL with SDL_INIT_VIDEO : %s", SDL_GetError());
		}
	}

	TEST(Init) {
		auto renderer = Renderer();

		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			auto win = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_HIDDEN);
			CHECK_EQUAL(true, renderer.init(win, -1, 0));
			renderer.destroy();
			SDL_DestroyWindow(win);
			SDL_Quit();
			CHECK(renderer.getHandle() == nullptr);
		} else {
			SDL_Log("Could not init SDL with SDL_INIT_VIDEO : %s", SDL_GetError());
		}
	}

	TEST(EqualsOpertator) {
		auto renderer = Renderer();

		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			auto win = SDL_CreateWindow("", 0, 0, 1, 1, SDL_WINDOW_HIDDEN);
			CHECK_EQUAL(true, renderer.init(win, -1, 0));
			CHECK(renderer == renderer.getHandle());
			renderer.destroy();
			SDL_DestroyWindow(win);
			SDL_Quit();
		} else {
			SDL_Log("Could not init SDL with SDL_INIT_VIDEO : %s", SDL_GetError());
		}
	}

	TEST(InitSW) {
		auto renderer = Renderer();

		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			auto surf = SDL_CreateRGBSurface(0, 1, 1, 32,
			                                 0x000000ff,
			                                 0x0000ff00,
			                                 0x00ff0000,
			                                 0xff000000);

			CHECK_EQUAL(true, renderer.initSW(surf));
			SDL_FreeSurface(surf);
			SDL_Quit();
		} else {
			SDL_Log("Could not init SDL with SDL_INIT_VIDEO : %s", SDL_GetError());
		}
	}

	TEST(ErrorNullHandle) {
		auto renderer = Renderer();
		CHECK(nullptr == renderer.getHandle());
		CHECK_THROW(renderer.present(), std::runtime_error);
	}
}
