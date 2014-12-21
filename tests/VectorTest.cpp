#include <unittest++/UnitTest++.h>
#include <SDL2/SDL.h>
#include <sstream>
#include "Vector.h"

using namespace tiledl;

SUITE(Vector2Tests)
{

	TEST(Constructor) {
		auto vec = Vector();
		CHECK_EQUAL(0.0, vec.x);
		CHECK_EQUAL(0.0, vec.y);

		vec = Vector(1, 2);
		CHECK_EQUAL(1.0, vec.x);
		CHECK_EQUAL(2.0, vec.y);

		vec = Vector(4.0, 3.0);
		CHECK_EQUAL(4.0, vec.x);
		CHECK_EQUAL(3.0, vec.y);

		SDL_Point pt;
		pt.x = 10;
		pt.y = 2;
		vec = Vector(pt);
		CHECK_EQUAL(10, vec.x);
		CHECK_EQUAL(2, vec.y);
	}

	TEST(CopyConstructor) {
		auto vec = Vector(1, 2);
		auto vec2 = Vector(vec);

		CHECK(&vec != &vec2);

		CHECK_EQUAL(vec.x, vec2.x);
		CHECK(&vec.x != &vec2.x);

		CHECK_EQUAL(vec.y, vec2.y);
		CHECK(&vec.y != &vec2.y);
	}

	TEST(XYConstructor) {
		auto vec = Vector(1);

		CHECK(&vec.x != &vec.y);

		CHECK_EQUAL(1, vec.x);
		CHECK_EQUAL(1, vec.y);
		CHECK_EQUAL(vec.x, vec.y);
	}

	TEST(Equals) {
		auto vec1 = Vector();
		auto vec2 = Vector();

		CHECK_EQUAL(true, vec1 == vec2);

		vec1 = Vector(1.0, 2.0);
		vec2 = Vector(1.0, 1.0);
		CHECK_EQUAL(false, vec1 == vec2);

		vec1 = Vector(2.0, 1.0);
		vec2 = Vector(1.0, 1.0);
		CHECK_EQUAL(false, vec1 == vec2);
	}

	TEST(NOT_Equals) {
		auto vec1 = Vector();
		auto vec2 = Vector();

		CHECK_EQUAL(false, vec1 != vec2);

		vec1 = Vector(1.0, 2.0);
		vec2 = Vector(1.0, 1.0);
		CHECK_EQUAL(true, vec1 != vec2);

		vec1 = Vector(1, 2);
		vec2 = Vector(1, 1);
		CHECK_EQUAL(true, vec1 != vec2);

		vec1 = Vector(2.0, 1.0);
		vec2 = Vector(1.0, 1.0);
		CHECK_EQUAL(true, vec1 != vec2);

		vec1 = Vector(2, 1);
		vec2 = Vector(1, 1);
		CHECK_EQUAL(true, vec1 != vec2);
	}

	TEST(Multiplaction) {
		auto vec = Vector(1, 2);

		// Times by double
		vec = vec * 2.0;
		CHECK_EQUAL(2.0, vec.x);
		CHECK_EQUAL(4.0, vec.y);

		vec = vec * 0.1;
		CHECK_EQUAL(0.2, vec.x);
		CHECK_EQUAL(0.4, vec.y);

		// Times by Vector
		vec = Vector(1, 2);
		vec = vec * Vector(2, 4);
		CHECK_EQUAL(2.0, vec.x);
		CHECK_EQUAL(8.0, vec.y);

		vec = Vector(1, 2);
		vec = vec * Vector(0.1, 0.2);
		CHECK_EQUAL(0.1, vec.x);
		CHECK_EQUAL(0.4, vec.y);
	}

	TEST(Division) {
		auto vec = Vector(1, 2);

		// Times by double
		vec = vec / 2.0;
		CHECK_EQUAL(0.5, vec.x);
		CHECK_EQUAL(1.0, vec.y);

		vec = vec / 0.1;
		CHECK_EQUAL(5.0, vec.x);
		CHECK_EQUAL(10.0, vec.y);

		// Times by Vector
		vec = Vector(1, 2);
		vec = vec / Vector(2, 4);
		CHECK_EQUAL(0.5, vec.x);
		CHECK_EQUAL(0.5, vec.y);

		vec = Vector(1, 2);
		vec = vec / Vector(0.1, 0.2);
		CHECK_EQUAL(10.0, vec.x);
		CHECK_EQUAL(10.0, vec.y);
	}

	TEST(Addition) {
		auto vec = Vector(1, 2);

		// Times by double
		vec = vec + 2.0;
		CHECK_EQUAL(3.0, vec.x);
		CHECK_EQUAL(4.0, vec.y);

		vec = vec + 0.1;
		CHECK_EQUAL(3.1, vec.x);
		CHECK_EQUAL(4.1, vec.y);

		// Times by Vector
		vec = Vector(1, 2);
		vec = vec + Vector(2, 4);
		CHECK_EQUAL(3, vec.x);
		CHECK_EQUAL(6, vec.y);

		vec = Vector(1, 2);
		vec = vec + Vector(0.1, 0.2);
		CHECK_EQUAL(1.1, vec.x);
		CHECK_EQUAL(2.2, vec.y);
	}

	TEST(Subtracktion) {
		auto vec = Vector(1, 2);

		// Times by double
		vec = vec - 2.0;
		CHECK_EQUAL(-1.0, vec.x);
		CHECK_EQUAL(0.0, vec.y);

		vec = vec - 0.1;
		CHECK_EQUAL(-1.1, vec.x);
		CHECK_EQUAL(-0.1, vec.y);

		// Times by Vector
		vec = Vector(1, 2);
		vec = vec - Vector(2, 4);
		CHECK_EQUAL(-1.0, vec.x);
		CHECK_EQUAL(-2.0, vec.y);

		vec = Vector(1, 2);
		vec = vec - Vector(0.1, 0.2);
		CHECK_EQUAL(0.9, vec.x);
		CHECK_EQUAL(1.8, vec.y);
	}

	TEST(OutStreamOpertator) {
		auto vec = Vector(1, 2);
		std::stringstream ss;
		ss << vec;

		CHECK_ARRAY_EQUAL("{1,2}", ss.str().c_str(), 5);
	}

	TEST(toSDLPoint) {
		auto vec = Vector();
		auto pt = vec.toSDLPoint();
		CHECK_EQUAL(0, pt.x);
		CHECK_EQUAL(0, pt.y);

		vec = Vector(10, 0);
		pt = vec.toSDLPoint();
		CHECK_EQUAL(10, pt.x);
		CHECK_EQUAL(0, pt.y);

		vec = Vector(10, 10);
		pt = vec.toSDLPoint();
		CHECK_EQUAL(10, pt.x);
		CHECK_EQUAL(10, pt.y);

		vec = Vector(0, 10);
		pt = vec.toSDLPoint();
		CHECK_EQUAL(0, pt.x);
		CHECK_EQUAL(10, pt.y);
	}
}
