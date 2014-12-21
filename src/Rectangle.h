#ifndef RECTANGLE_H_
#define RECTANGLE_H_
#pragma once

#include <SDL2/SDL_rect.h>
#include <iostream>
#include "Vector.h"

namespace tiledl
{
	class Rectangle : public SDL_Rect
	{
	public:
		Rectangle();
		Rectangle(int x, int y, int width, int height);
		Rectangle(const SDL_Rect& rect);
		Rectangle(const Rectangle& rect);

		bool operator==(const Rectangle& other) const;
		bool operator!=(const Rectangle& other) const;

		bool isInside(const Vector& vec);
		bool isInside(const SDL_Point& vec);

		bool intersects(const SDL_Rect& rect);
		bool intersects(const Rectangle& rect);


		SDL_Rect toSdlRect() const;

		static Rectangle Empty;
	};
	std::ostream& operator<< (std::ostream& out, const Rectangle& rect);
} // namespace frame2d

#endif // RECTANGLE_H_
