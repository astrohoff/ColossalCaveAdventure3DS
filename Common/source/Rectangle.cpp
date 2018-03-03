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

Vector2D Rectangle::GetMaxPosition() const
{
	return minPosition + size;
}

Vector2D Rectangle::GetCenter() const
{
	return minPosition + size / 2;
}

void Rectangle::SetPosition(const Vector2D& position)
{
	minPosition.Set(position);
}

float Rectangle::GetAspectRatio() const
{
	return size.x / size.y;
}

bool Rectangle::Contains(const Vector2D& point) const
{
	Vector2D maxPos = GetMaxPosition();
	bool isContained = point.x >= minPosition.x;
	isContained = isContained && point.x <= maxPos.x;
	isContained = isContained && point.y >= minPosition.y;
	isContained = isContained && point.y <= maxPos.y;
	return isContained;
}

Rectangle Rectangle::GetPaddedRect(const Vector2D& padding) const
{
	Vector2D posDiff(-padding.x, -padding.y);
	Vector2D sizeDiff(2 * padding.x, 2 * padding.y);
	Vector2D paddedPos = minPosition + posDiff;
	Vector2D paddedSize = size + sizeDiff;
	if (paddedSize.x < 0 || paddedSize.y < 0) {
		paddedPos = minPosition;
		paddedSize = size;
	}
	return Rectangle(paddedPos, paddedSize);
}

void Rectangle::ApplyAspectRatio(float newAspect, bool shrink) {
	float aspect = GetAspectRatio();
	if (aspect == newAspect)
	{
		return;
	}
	Vector2D newSize;
	bool lockX = (newAspect > aspect && shrink) || (newAspect < aspect && !shrink);
	if (lockX) 
	{
		newSize = Vector2D(size.x, size.x / newAspect);
	}
	else
	{
		newSize = Vector2D(size.y * newAspect, size.y);
	}
	Vector2D sizeDiff = size - newSize;
	size = newSize;
	minPosition += sizeDiff / 2;
}