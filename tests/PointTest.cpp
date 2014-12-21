#include <unittest++/UnitTest++.h>
#include <sstream>
#include <stdexcept>
#include "Point.h"

using namespace tiledl;

SUITE(PointTests)
{
	TEST(Constructor) {
		auto vec = Point();
		CHECK_EQUAL(0, vec.x);
		CHECK_EQUAL(0, vec.y);

		vec = Point(1, 2);
		CHECK_EQUAL(1, vec.x);
		CHECK_EQUAL(2, vec.y);

		vec = Point(4, 3);
		CHECK_EQUAL(4, vec.x);
		CHECK_EQUAL(3, vec.y);

		SDL_Point pt;
		pt.x = 10;
		pt.y = 2;
		vec = Point(pt);
		CHECK_EQUAL(10, vec.x);
		CHECK_EQUAL(2, vec.y);
	}

	TEST(CopyConstructor) {
		auto vec = Point(1, 2);
		auto vec2 = Point(vec);

		CHECK(&vec != &vec2);

		CHECK_EQUAL(vec.x, vec2.x);
		CHECK(&vec.x != &vec2.x);

		CHECK_EQUAL(vec.y, vec2.y);
		CHECK(&vec.y != &vec2.y);
	}

	TEST(XYConstructor) {
		auto vec = Point(1);

		CHECK(&vec.x != &vec.y);

		CHECK_EQUAL(1, vec.x);
		CHECK_EQUAL(1, vec.y);
		CHECK_EQUAL(vec.x, vec.y);
	}

	TEST(Equals) {
		auto vec1 = Point();
		auto vec2 = Point();

		CHECK_EQUAL(true, vec1 == vec2);

		vec1 = Point(1, 2);
		vec2 = Point(1, 1);
		CHECK_EQUAL(false, vec1 == vec2);

		vec1 = Point(2, 1);
		vec2 = Point(1, 1);
		CHECK_EQUAL(false, vec1 == vec2);
	}

	TEST(NOT_Equals) {
		auto vec1 = Point();
		auto vec2 = Point();

		CHECK_EQUAL(false, vec1 != vec2);

		vec1 = Point(1, 2);
		vec2 = Point(1, 1);
		CHECK_EQUAL(true, vec1 != vec2);

		vec1 = Point(1, 2);
		vec2 = Point(1, 1);
		CHECK_EQUAL(true, vec1 != vec2);

		vec1 = Point(2, 1);
		vec2 = Point(1, 1);
		CHECK_EQUAL(true, vec1 != vec2);

		vec1 = Point(2, 1);
		vec2 = Point(1, 1);
		CHECK_EQUAL(true, vec1 != vec2);
	}

	TEST(Multiplaction) {
		auto vec = Point(1, 2);

		// Times by double
		vec = vec * 2;
		CHECK_EQUAL(2, vec.x);
		CHECK_EQUAL(4, vec.y);

		vec = vec * 0.1;
		CHECK_EQUAL(0, vec.x);
		CHECK_EQUAL(0, vec.y);

		// Times by Point
		vec = Point(1, 2);
		vec = vec * Point(2, 4);
		CHECK_EQUAL(2, vec.x);
		CHECK_EQUAL(8, vec.y);

		vec = Point(1, 2);
		vec = vec * Point(0.1, 0.2);
		CHECK_EQUAL(0, vec.x);
		CHECK_EQUAL(0, vec.y);
	}

	TEST(Division) {
		auto vec = Point(1, 2);

		// Divide by int
		vec = vec / 2;
		CHECK_EQUAL(0, vec.x);
		CHECK_EQUAL(1, vec.y);

		// Divide by Point
		vec = Point(4, 8);
		vec = vec / Point(2, 4);
		CHECK_EQUAL(2, vec.x);
		CHECK_EQUAL(2, vec.y);
	}

	TEST(DivideByZero) {
		auto vec = Point(1, 2);
		CHECK_THROW(vec / Point(0, 0), std::invalid_argument);
		CHECK_THROW(vec / 0, std::invalid_argument);
	}

	TEST(Addition) {
		auto vec = Point(1, 2);

		// add by int
		vec = vec + 2;
		CHECK_EQUAL(3, vec.x);
		CHECK_EQUAL(4, vec.y);

		// add by Point
		vec = Point(1, 2);
		vec = vec + Point(2, 4);
		CHECK_EQUAL(3, vec.x);
		CHECK_EQUAL(6, vec.y);
	}

	TEST(Subtracktion) {
		auto vec = Point(1, 2);

		// Subract a double
		vec = vec - 2;
		CHECK_EQUAL(-1, vec.x);
		CHECK_EQUAL(0, vec.y);

		// Times by Point
		vec = Point(1, 2);
		vec = vec - Point(2, 4);
		CHECK_EQUAL(-1, vec.x);
		CHECK_EQUAL(-2, vec.y);
	}

	TEST(OutStreamOpertator) {
		auto vec = Point(1, 2);
		std::stringstream ss;
		ss << vec;

		CHECK_ARRAY_EQUAL("{1,2}", ss.str().c_str(), 5);
	}

	TEST(toSDLPoint) {
		auto vec = Point();
		auto pt = (SDL_Point)vec;
		CHECK_EQUAL(0, pt.x);
		CHECK_EQUAL(0, pt.y);

		vec = Point(10, 0);
		pt = (SDL_Point)vec;
		CHECK_EQUAL(10, pt.x);
		CHECK_EQUAL(0, pt.y);

		vec = Point(10, 10);
		pt = (SDL_Point)vec;
		CHECK_EQUAL(10, pt.x);
		CHECK_EQUAL(10, pt.y);

		vec = Point(0, 10);
		pt = (SDL_Point)vec;
		CHECK_EQUAL(0, pt.x);
		CHECK_EQUAL(10, pt.y);
	}

	// Tests for the validity of assumptions made with extending SDL_Point
	TEST(SizeofToSdlPoint) {
		CHECK_EQUAL(sizeof(SDL_Point), sizeof(Point));
	}

	TEST(SDLPointPointerCheck) {
		auto pt = Point(1, 2);
		SDL_Point* sdlpt = nullptr;

		sdlpt = (SDL_Point*)(&pt);
		CHECK_EQUAL(sdlpt->x, pt.x);
		CHECK_EQUAL(sdlpt->y, pt.y);
	}
}
