#include "Point.h"
#include <stdexcept>

using namespace tiledl;

Point::Point()
{
	this->x = this->y = 0;
}

Point::Point(const SDL_Point& pt)
{
	this->x = pt.x;
	this->y = pt.y;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point(int xy)
{
	this->x = this-> y = xy;
}

Point::Point(const Point& other)
{
	this->x = other.x;
	this->y = other.y;
}

bool Point::operator==(const Point& other) const
{
	return (this->x == other.x && this->y == other.y);
}

bool Point::operator!=(const Point& other) const
{
	return (this->x != other.x || this->y != other.y);
}

Point Point::operator+(const Point& added) const
{
	auto result = Point(*this);
	result.x += added.x;
	result.y += added.y;
	return result;
}

Point Point::operator+(const int& added) const
{
	auto result = Point(*this);
	result.x += added;
	result.y += added;
	return result;
}

Point Point::operator-(const Point& subed) const
{
	auto result = Point(*this);
	result.x -= subed.x;
	result.y -= subed.y;
	return result;
}

Point Point::operator-(const int& subed) const
{
	auto result = Point(*this);
	result.x -= subed;
	result.y -= subed;
	return result;
}

Point Point::operator*(const Point& factor) const
{
	auto result = Point(*this);
	result.x *= factor.x;
	result.y *= factor.y;
	return result;
}
Point Point::operator*(const int& factor) const
{
	auto result = Point(*this);
	result.x *= factor;
	result.y *= factor;
	return result;
}

Point Point::operator/(const Point& factor) const
{
	if (factor.x == 0 || factor.y == 0)
		throw std::invalid_argument("A Point cannot be divided by 0");

	auto result = Point(*this);
	result.x /= factor.x;
	result.y /= factor.y;
	return result;
}

Point Point::operator/(const int& factor) const
{
	if (factor == 0)
		throw std::invalid_argument("A Point cannot be divided by 0");

	auto result = Point(*this);
	result.x /= factor;
	result.y /= factor;
	return result;
}

std::ostream& tiledl::operator<<(std::ostream& out, const Point& pt)
{
	out << "{" << pt.x << "," << pt.y << "}";
	return out;
}
