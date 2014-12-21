#include <unittest++/UnitTest++.h>

#include "Rectangle.h"
#include <sstream>

using namespace tiledl;

SUITE(RectangleTests)
{

	TEST(EmptyRect) {
		CHECK_EQUAL(0, Rectangle::Empty.x);
		CHECK_EQUAL(0, Rectangle::Empty.y);
		CHECK_EQUAL(0, Rectangle::Empty.w);
		CHECK_EQUAL(0, Rectangle::Empty.h);
	}

	TEST(Constructor) {
		auto rect = Rectangle();

		CHECK_EQUAL(Rectangle::Empty, rect);
	}
	TEST(ConstructorInts) {
		auto rect = Rectangle(1, 2, 3, 4);
		CHECK_EQUAL(1, rect.x);
		CHECK_EQUAL(2, rect.y);
		CHECK_EQUAL(3, rect.w);
		CHECK_EQUAL(4, rect.h);
	}
	TEST(ConstructorCopy) {
		auto rect = Rectangle(Rectangle(4, 3, 2, 1));
		CHECK_EQUAL(4, rect.x);
		CHECK_EQUAL(3, rect.y);
		CHECK_EQUAL(2, rect.w);
		CHECK_EQUAL(1, rect.h);
	}
	TEST(ConstructorSDLCopy) {
		SDL_Rect rec;
		rec.x = rec.y = rec.w = rec.h = 0;
		auto rect = Rectangle(rec);
		CHECK_EQUAL(Rectangle::Empty, rect);
	}

	TEST(EqualsOperator) {
		auto rect = Rectangle();
		CHECK_EQUAL(true , rect == Rectangle::Empty);

		rect = Rectangle(1, 0, 0, 0);
		CHECK_EQUAL(false, rect == Rectangle::Empty);

		rect = Rectangle(0, 1, 0, 0);
		CHECK_EQUAL(false, rect == Rectangle::Empty);

		rect = Rectangle(0, 0, 1, 0);
		CHECK_EQUAL(false, rect == Rectangle::Empty);

		rect = Rectangle(0, 0, 0, 1);
		CHECK_EQUAL(false, rect == Rectangle::Empty);
	}

	TEST(NotEqualsOperator) {
		auto rect = Rectangle();
		CHECK_EQUAL(false, rect != Rectangle::Empty);

		rect = Rectangle(1, 0, 0, 0);
		CHECK_EQUAL(true, rect != Rectangle::Empty);

		rect = Rectangle(0, 1, 0, 0);
		CHECK_EQUAL(true, rect != Rectangle::Empty);

		rect = Rectangle(0, 0, 1, 0);
		CHECK_EQUAL(true, rect != Rectangle::Empty);

		rect = Rectangle(0, 0, 0, 1);
		CHECK_EQUAL(true, rect != Rectangle::Empty);
	}

	TEST(OutStreamOpertator) {
		auto rect = Rectangle(1, 2, 3, 4);
		std::stringstream ss;

		ss << rect;

		CHECK_ARRAY_EQUAL("{1,2,3,4}", ss.str().c_str(), 9);
	}

	TEST(isInside) {
		auto rect = Rectangle(0, 0, 10, 10);
		auto vec = Vector(1, 2);
		auto pt = vec.toSDLPoint();

		CHECK_EQUAL(true, rect.isInside(vec));
		CHECK_EQUAL(true, rect.isInside(pt));

		vec = Vector(-1, 2);
		pt = vec.toSDLPoint();

		CHECK_EQUAL(false, rect.isInside(vec));
		CHECK_EQUAL(false, rect.isInside(pt));

		vec = Vector(1, -2);
		pt = vec.toSDLPoint();

		CHECK_EQUAL(false, rect.isInside(vec));
		CHECK_EQUAL(false, rect.isInside(pt));

		vec = Vector(-1, -2);
		pt = vec.toSDLPoint();

		CHECK_EQUAL(false, rect.isInside(vec));
		CHECK_EQUAL(false, rect.isInside(pt));
	}

	TEST(SizeoFWithSdlRect) {
		CHECK_EQUAL(sizeof(SDL_Rect), sizeof(Rectangle));
	}

	TEST(Intercets) {
		auto rectA = Rectangle(0, 0, 10, 10);
		auto rectB = Rectangle(0, 0, 10, 10);

		CHECK_EQUAL(true, rectA.intersects(rectB));
		CHECK_EQUAL(true, rectB.intersects(rectA));

		rectB = Rectangle(10, 10, 10, 10);
		CHECK_EQUAL(false, rectA.intersects(rectB));
		CHECK_EQUAL(false, rectB.intersects(rectA));
	}
}
