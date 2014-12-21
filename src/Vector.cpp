#include "Vector.h"

using namespace tiledl;

Vector::Vector()
{
	x = y = 0.0;
}

Vector::Vector(int xy)
{
	this->y = this->x = xy;
}

Vector::Vector(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector::Vector(double xy)
{
	this->y = this->x = xy;
}

Vector::Vector(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vector::Vector(const Vector& copy)
{
	this->x = copy.x;
	this->y = copy.y;
}

Vector::Vector(const SDL_Point& pt)
{
	this->x = pt.x;
	this->y = pt.y;
}

bool Vector::operator==(const Vector& other) const
{
	return (x == other.x && y == other.y);
}

bool Vector::operator!=(const Vector& other) const
{
	return (x != other.x || y != other.y);
}

Vector Vector::operator*(const double& factor) const
{
	auto result = Vector(*this);
	result.x *= factor;
	result.y *= factor;
	return result;
}

Vector Vector::operator*(const Vector& factor) const
{
	auto result = Vector(*this);
	result.x *= factor.x;
	result.y *= factor.y;
	return result;
}

Vector Vector::operator/(const double& factor) const
{
	auto result = Vector(*this);
	result.x /= factor;
	result.y /= factor;
	return result;
}

Vector Vector::operator/(const Vector& factor) const
{
	auto result = Vector(*this);
	result.x /= factor.x;
	result.y /= factor.y;
	return result;
}

Vector Vector::operator+(const Vector& added) const
{
	Vector result = Vector(*this);
	result.x += added.x;
	result.y += added.y;
	return result;
}

Vector Vector::operator+(const double& added) const
{
	Vector result = Vector(*this);
	result.x += added;
	result.y += added;
	return result;
}

Vector Vector::operator-(const double& subed) const
{
	Vector result = Vector(*this);
	result.x -= subed;
	result.y -= subed;
	return result;
}

Vector Vector::operator-(const Vector& subed) const
{
	Vector result = Vector(*this);
	result.x -= subed.x;
	result.y -= subed.y;
	return result;
}

std::ostream& tiledl::operator<<(std::ostream& out, const Vector& vec)
{
	out << "{" << vec.x << "," << vec.y << "}";
	return out;
}

SDL_Point Vector::toSDLPoint() const
{
	return SDL_Point { (int)this->x, (int)this->y};
}

