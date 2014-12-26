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

	TEST(ConstructorUint8) {
		Uint8 r = 5, g = 10, b = 100, a = 128;
		auto color = Color(r, g, b , a);
		CHECK_EQUAL(5, color.r);
		CHECK_EQUAL(10, color.g);
		CHECK_EQUAL(100, color.b);
		CHECK_EQUAL(128, color.a);

		color = Color(r, g, b);
		CHECK_EQUAL(5, color.r);
		CHECK_EQUAL(10, color.g);
		CHECK_EQUAL(100, color.b);
		CHECK_EQUAL(255, color.a);
	}

	TEST(Constructorint) {
		auto color = Color(255, 256, 10 , 15);
		CHECK_EQUAL(255, color.r);
		CHECK_EQUAL(0, color.g);
		CHECK_EQUAL(10, color.b);
		CHECK_EQUAL(15, color.a);

		color = Color(125, 257, 10);
		CHECK_EQUAL(125, color.r);
		CHECK_EQUAL(1, color.g);
		CHECK_EQUAL(10, color.b);
		CHECK_EQUAL(255, color.a);
	}

	TEST(Constructorintrgba) {
		auto color = Color(0xffaa0013);
		CHECK_EQUAL(0xff, color.r);
		CHECK_EQUAL(0xaa, color.g);
		CHECK_EQUAL(0x00, color.b);
		CHECK_EQUAL(0x13, color.a);

		color = Color(0xffaa0013, tiledl::BIG_ENDIAN_ORDER);
		CHECK_EQUAL(0x13, color.r);
		CHECK_EQUAL(0x00, color.g);
		CHECK_EQUAL(0xaa, color.b);
		CHECK_EQUAL(0xff, color.a);

		color = Color(0xffaa0013, tiledl::LITTLE_ENDIAN_ORDER);
		CHECK_EQUAL(0xff, color.r);
		CHECK_EQUAL(0xaa, color.g);
		CHECK_EQUAL(0x00, color.b);
		CHECK_EQUAL(0x13, color.a);

		color = Color(0xffaa0013, tiledl::SYSTEM_ORDER);
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		CHECK_EQUAL(0x13, color.r);
		CHECK_EQUAL(0x00, color.g);
		CHECK_EQUAL(0xaa, color.b);
		CHECK_EQUAL(0xff, color.a);

#else
		CHECK_EQUAL(0xff, color.r);
		CHECK_EQUAL(0xaa, color.g);
		CHECK_EQUAL(0x00, color.b);
		CHECK_EQUAL(0x13, color.a);
#endif

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
		CHECK_EQUAL(0, a.r);
		CHECK_EQUAL(0, a.g);
		CHECK_EQUAL(0, a.b);
		CHECK_EQUAL(0, a.a);
	}

	TEST(Size) {
		SDL_Color a {255, 254, 253 , 252};
		auto b = Color(a);
		CHECK_EQUAL(sizeof(a), sizeof(b));
	}
}
