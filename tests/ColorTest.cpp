#include <unittest++/UnitTest++.h>
#include <SDL2/SDL.h>
#include "Color.h"

using namespace tiledl;

SUITE(ColorTests)
{
	TEST(ConstructorCopy) {
		SDL_Color a {255, 254, 253 , 252};
		auto b = Color(a);
		CHECK_EQUAL(255, b.r);
		CHECK_EQUAL(254, b.g);
		CHECK_EQUAL(253, b.b);
		CHECK_EQUAL(252, b.a);
	}

	TEST(ConvertToSDLColor) {
		SDL_Color a {255, 254, 253 , 252};
		auto b = Color(a);
		CHECK_EQUAL(255, b.r);
		CHECK_EQUAL(254, b.g);
		CHECK_EQUAL(253, b.b);
		CHECK_EQUAL(252, b.a);

		b.r = b.g = b.b = b.a = 0;
		a = (SDL_Color)b;
		CHECK_EQUAL(000, a.r);
		CHECK_EQUAL(000, a.g);
		CHECK_EQUAL(000, a.b);
		CHECK_EQUAL(000, a.a);
	}

	TEST(Size) {
		SDL_Color a {255, 254, 253 , 252};
		auto b = Color(a);
		CHECK_EQUAL(sizeof(a), sizeof(b));
	}
}
