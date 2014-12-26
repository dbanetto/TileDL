#include "Color.h"
#include <limits>
using namespace tiledl;

Color::Color(SDL_Color& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(Uint8 r, Uint8 g, Uint8 b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}

Color::Color(int r, int g, int b, int a)
{
	this->r = (Uint8)(r);
	this->g = (Uint8)(g);
	this->b = (Uint8)(b);
	this->a = (Uint8)(a);
}

Color::Color(int r, int g, int b)
{
	this->r = (Uint8)(r % 256);
	this->g = (Uint8)(g % 256);
	this->b = (Uint8)(b % 256);
	this->a = 255;
}

/**
 * @brief Follows HTML-styled hex notation of byte order of RGBA
 *
 * @param rgba an int containing a RGBA8888 color
 */
Color::Color(int rgba)
{
	this->r = (Uint8)((rgba >> 24) % 256);
	this->g = (Uint8)((rgba >> 16) % 256);
	this->b = (Uint8)((rgba >>  8) % 256);
	this->a = (Uint8)((rgba >>  0) % 256);
}

/**
 * @brief Load Color from int using byte desired ordering
 *
 * @param rgba an int containing a RGBA8888 color
 * @param order Byte order to use
 */
Color::Color(int rgba, ColorByteOrder order)
{
	switch (order) {
		case(LITTLE_ENDIAN_ORDER):
			this->r = (Uint8)((rgba >> 24) % 256);
			this->g = (Uint8)((rgba >> 16) % 256);
			this->b = (Uint8)((rgba >>  8) % 256);
			this->a = (Uint8)((rgba >>  0) % 256);
			break;
		case(BIG_ENDIAN_ORDER):
			this->r = (Uint8)((rgba >>  0) % 256);
			this->g = (Uint8)((rgba >>  8) % 256);
			this->b = (Uint8)((rgba >> 16) % 256);
			this->a = (Uint8)((rgba >> 24) % 256);
			break;
		case(SYSTEM_ORDER):
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			this->r = (Uint8)((rgba >>  0) % 256);
			this->g = (Uint8)((rgba >>  8) % 256);
			this->b = (Uint8)((rgba >> 16) % 256);
			this->a = (Uint8)((rgba >> 24) % 256);
#else
			this->r = (Uint8)((rgba >> 24) % 256);
			this->g = (Uint8)((rgba >> 16) % 256);
			this->b = (Uint8)((rgba >>  8) % 256);
			this->a = (Uint8)((rgba >>  0) % 256);
#endif
			break;
	}
}
