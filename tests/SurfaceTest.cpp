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

	TEST(Resize) {
		auto surf = Surface(10,15);
		CHECK(nullptr != surf.getHandle());
		CHECK_EQUAL(10, surf.getWidth());
		CHECK_EQUAL(15, surf.getHeight());

		surf.resize(15,10);
		CHECK(nullptr != surf.getHandle());
		CHECK_EQUAL(15, surf.getWidth());
		CHECK_EQUAL(10, surf.getHeight());
	}

	TEST(ResizeStretch) {
		auto surf = Surface(10,20);
		CHECK(nullptr != surf.getHandle());
		CHECK_EQUAL(10, surf.getWidth());
		CHECK_EQUAL(20, surf.getHeight());

		Rectangle rect(0,0,5,20);
		if (SDL_FillRect(surf.getHandle(), &rect, SDL_MapRGB(surf.getFormat(), 255u, 0u, 0u) ) != 0) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			            "Error while calling SDL_FillRect : %s",
			            SDL_GetError()
			);
		}
		rect.x = 5; // {5,0,5,20}
		if (SDL_FillRect(surf.getHandle(), &rect, SDL_MapRGB(surf.getFormat(), 0u, 255u, 0u) ) != 0) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			            "Error while calling SDL_FillRect : %s",
			            SDL_GetError()
			);
		}

		// TODO: Check if left side is Red and right green

		surf.resize(20,10);
		CHECK(nullptr != surf.getHandle());
		CHECK_EQUAL(20, surf.getWidth());
		CHECK_EQUAL(10, surf.getHeight());

		// TODO: Check if left side is Red and right blue with altered middle line
	}

}
