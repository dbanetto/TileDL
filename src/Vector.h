#ifndef VECTOR2_H
#define VECTOR2_H
#pragma once

#include <ostream>
#include <SDL2/SDL.h>

namespace tiledl
{

	class Vector
	{
	public:
		Vector();
		Vector(const Vector& copy);

		Vector(int xy);
		Vector(int x, int y);

		Vector(double xy);
		Vector(double x, double y);
		Vector(const SDL_Point& pt);


		bool operator==(const Vector& other) const;
		bool operator!=(const Vector& other) const;

		Vector operator*(const double& factor) const;
		Vector operator*(const Vector& factor) const;

		Vector operator/(const double& factor) const;
		Vector operator/(const Vector& factor) const;

		Vector operator+(const double& added) const;
		Vector operator+(const Vector& added) const;

		Vector operator-(const double& subed) const;
		Vector operator-(const Vector& subed) const;

		SDL_Point toSDLPoint() const;

		double x, y;
	};
	std::ostream& operator<< (std::ostream& out, const Vector& vec);

} // namespace frame2d
#endif // VECTOR2_H
