#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}


void Vector2D::Set(const Vector2D& vect2D)
{
	x = vect2D.x;
	y = vect2D.y;
}


Vector2D Vector2D::operator+(const Vector2D& v) const
{
	float sumX = x + v.x;
	float sumY = y + v.y;
	return Vector2D(sumX, sumY);
}

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	float diffX = x - v.x;
	float diffY = y - v.y;
	return Vector2D(diffX, diffY);
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2D Vector2D::operator/(float f) const
{
	return Vector2D(x / f, y / f);
}

Vector2D& Vector2D::operator/=(float f)
{
	x /= f;
	y /= f;
	return *this;
}

Vector2D Vector2D::operator*(float f) const
{
	return Vector2D(x * f, y * f);
}

Vector2D& Vector2D::operator*=(float f)
{
	x *= f;
	y *= f;
	return *this;
}

bool Vector2D::operator==(const Vector2D& v) const
{
	return x == v.x && y == v.y;
}

bool Vector2D::operator!=(const Vector2D& v) const
{
	return x != v.x || y != v.y;
}