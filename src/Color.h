#ifndef COLOR_H_
#define COLOR_H_
#pragma once

#include <SDL2/SDL.h>

namespace tiledl
{
	struct Color : public SDL_Color {
	public:
		Color(SDL_Color& c);
	};
}

#endif
