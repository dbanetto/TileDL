#ifndef COLOR_H_
#define COLOR_H_
#pragma once

#include <SDL2/SDL.h>

namespace tiledl
{
	enum ColorByteOrder {
		LITTLE_ENDIAN_ORDER,
		BIG_ENDIAN_ORDER,
		SYSTEM_ORDER
	};

	struct Color : public SDL_Color {
	public:
		Color(SDL_Color& c);
		Color(Uint8 r, Uint8 gr, Uint8 b, Uint8 a);
		Color(Uint8 r, Uint8 gr, Uint8 b);
		Color(int r, int gr, int b, int a);
		Color(int r, int gr, int b);
		Color(int rgba);
		Color(int rgba, ColorByteOrder order);
	};
}

#endif
