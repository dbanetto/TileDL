#include "Rectangle.h"
#include <iostream>
#include <SDL2/SDL_rect.h>

using namespace tiledl;

Rectangle Rectangle::Empty = Rectangle();

/**
 * @brief constructor initializes all values 0
 *
 */
Rectangle::Rectangle()
{
	x = y = w = h = 0;
}

/**
 * @brief Fully specified constructor
 */
Rectangle::Rectangle(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

/**
 * @param rect values to be copied
 */
Rectangle::Rectangle(const SDL_Rect& rect)
{
	this->x = rect.x;
	this->y = rect.y;
	this->w = rect.w;
	this->h = rect.h;
}

/**
 * @param rect values to be copied
 */
Rectangle::Rectangle(const Rectangle& rect)
{
	this->x = rect.x;
	this->y = rect.y;
	this->w = rect.w;
	this->h = rect.h;
}

bool Rectangle::operator==(const Rectangle& other) const
{
	return (this->x == other.x &&
	        this->y == other.y &&
	        this->w == other.w &&
	        this->h == other.h);
}

bool Rectangle::operator!=(const Rectangle& other) const
{
	return !(*this == other);
}

SDL_Rect Rectangle::toSdlRect() const
{
	SDL_Rect r;
	r.x = this->x;
	r.y = this->y;
	r.w = this->w;
	r.h = this->h;
	return r;
}

/**
 * @brief Checks if a Vector is inside the rectangle
 *
 * @param vec Vector to check
 * @return bool is true if the vector is in the rectangle
 */
bool Rectangle::isInside(const Vector& vec)
{
	return (vec.x > this->x &&
	        vec.y > this->y &&
	        vec.x < this->x + this->w &&
	        vec.y < this->y + this->h);
}

/**
 * @brief Checks if a Point is inside the rectangle
 *
 * @param vec Vector to check
 * @return bool is true if the point is in the rectangle, false otherwise
 */
bool Rectangle::isInside(const SDL_Point& vec)
{
	return (vec.x > this->x &&
	        vec.y > this->y &&
	        vec.x < this->x + this->w &&
	        vec.y < this->y + this->h);
}

/**
 * @brief Checks if two rectangles intercept
 *
 * @return bool true if they intercept, false otherwise
 */
bool Rectangle::intersects(const Rectangle& rect)
{
	auto r = this->toSdlRect();
	auto o = rect.toSdlRect();
	return SDL_HasIntersection(&r, &o) == SDL_TRUE;
}

/**
 * @brief Checks if two rectangles intercept
 *
 * @return bool true if they intercept, false otherwise
 */
bool Rectangle::intersects(const SDL_Rect& rect)
{
	auto r = this->toSdlRect();
	return SDL_HasIntersection(&r, &rect) == SDL_TRUE;
}


/**
 * @brief standard output form for rectangle
 */
std::ostream& tiledl::operator<< (std::ostream& out, const Rectangle& rect)
{
	out << "{" << rect.x << "," << rect.y << "," << rect.w << "," << rect.h << "}";
	return out;
}
