#include "Rectangle.h"

// x,y defines bottom left corner. (Maybe can depend on use?)
Rectangle::Rectangle()
{
	minPosition = Vector2D(0, 0);
	size = Vector2D(10, 10);
}

Rectangle::Rectangle(Vector2D minPosition, Vector2D size)
{
	this->minPosition = minPosition;
	this->size = size;
}

Rectangle::Rectangle(float minX, float minY, float sizeX, float sizeY)
{
	minPosition = Vector2D(minX, minY);
	size = Vector2D(sizeX, sizeY);
}



const Vector2D& Rectangle::GetMinPosition() const
{
	return minPosition;
}

const Vector2D& Rectangle::GetSize() const
{
	return size;
}

void Rectangle::SetMinPosition(Vector2D position)
{
	minPosition = position;
}

void Rectangle::SetSize(Vector2D size)
{
	this->size = size;
}



Vector2D Rectangle::GetMaxPosition() const
{
	return minPosition + size;
}

Vector2D Rectangle::GetCenterPosition() const
{
	return minPosition + size / 2;
}

bool Rectangle::Contains(const Vector2D& point) const
{
	Vector2D maxPos = GetMaxPosition();
	return point.x >= minPosition.x && point.x <= maxPos.x &&
		   point.y >= minPosition.y && point.y <= maxPos.y;
}


Rectangle Rectangle::ConstructMinMax(Vector2D minPosition, Vector2D maxPosition)
{
	return Rectangle(minPosition, maxPosition - minPosition);
}


bool Rectangle::Contains(const Rectangle& otherRect) const
{
	Vector2D maxPos = GetMaxPosition();
	const Vector2D& otherMinPos = otherRect.GetMinPosition();
	Vector2D otherMaxPos = otherRect.GetMaxPosition();
	
	return minPosition.x <= otherMinPos.x && minPosition.y <= otherMinPos.y &&
			maxPos.x >= otherMaxPos.x && maxPos.y >= otherMaxPos.y;
}

bool Rectangle::Intersects(const Rectangle& otherRect) const
{
	Vector2D maxPos = GetMaxPosition();
	const Vector2D& otherMin = otherRect.GetMinPosition();
	Vector2D otherMax = otherRect.GetMaxPosition();
	
	return otherMin.x <= maxPos.x && otherMax.x >= minPosition.x &&
			otherMin.y <= maxPos.y && otherMax.y >= minPosition.y;
}

void Rectangle::Scale(float scale, ScaleOrigin origin)
{
	if(origin == ScaleOrigin::Center)
		minPosition = GetCenterPosition() - (size / 2) * scale;
	size *= scale;
}