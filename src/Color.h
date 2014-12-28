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
		Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		Color(Uint8 r, Uint8 g, Uint8 b);
		Color(int r, int g, int b, int a);
		Color(int r, int g, int b);
		Color(int rgba);
		Color(int rgba, ColorByteOrder order);

		Uint32 MapToRGB(SDL_PixelFormat* format);
		Uint32 MapToRGBA(SDL_PixelFormat* format);

	};
}

#endif
