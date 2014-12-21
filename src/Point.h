#ifndef POINT_H
#define POINT_H
#pragma once

#include <ostream>
#include <SDL2/SDL_rect.h>

namespace tiledl
{
	class Point : public SDL_Point
	{
	public:
		Point();
		Point(const Point& other);

		Point(int xy);
		Point(int x, int y);
		Point(const SDL_Point& pt);


		bool operator==(const Point& other) const;
		bool operator!=(const Point& other) const;

		Point operator*(const int& factor) const;
		Point operator*(const Point& factor) const;

		Point operator/(const int& factor) const;
		Point operator/(const Point& factor) const;

		Point operator+(const int& added) const;
		Point operator+(const Point& added) const;

		Point operator-(const int& subed) const;
		Point operator-(const Point& subed) const;
	};
	std::ostream& operator<< (std::ostream& out, const Point& vec);
}
#endif // POINT_H
