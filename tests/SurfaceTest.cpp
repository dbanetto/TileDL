#include <unittest++/UnitTest++.h>
#include "Surface.h"

using namespace tiledl;


SUITE(Surface)
{
	TEST(NullPtr) {
		auto surf = Surface();
		CHECK(nullptr == surf.getHandle());
	}

	TEST(CreateSurface) {
		auto surf = tiledl::CreateSurface(10,15);
		CHECK(nullptr != surf);
		CHECK_EQUAL(1 ,surf->refcount);

		SDL_FreeSurface(surf);
	}

	TEST(ConstructorWH) {
		auto surf = Surface(10,15);
		CHECK(nullptr != surf.getHandle());
		CHECK_EQUAL(10, surf.getWidth());
		CHECK_EQUAL(15, surf.getHeight());
	}

}
