#include "Color.h"

using namespace tiledl;

Color::Color(SDL_Color& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
	this->a = c.a;
}
