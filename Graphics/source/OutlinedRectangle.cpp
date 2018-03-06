#include "OutlinedRectangle.h"

OutlinedRectangle::OutlinedRectangle()
{
	outlineRect = Rectangle(0, 0, 10, 10);
	innerRect = Rectangle(1, 1, 8, 8);
	outlineColor = 0xFFFFFFFF;
	innerColor = 0x000000FF;
	depth = 0.5f;
}

OutlinedRectangle::OutlinedRectangle(Rectangle area, float depth)
{
	outlineRect = area;
	innerRect = Rectangle(area.GetMinPosition() + Vector2D(1, 1),
						   area.GetSize() - Vector2D(2, 2));
	outlineColor = 0xFFFFFFFF;
	innerColor = 0x000000FF;
	this->depth = depth;
}

void OutlinedRectangle::Draw() const
{
	CCAGraphics::DrawRectangle(outlineRect, depth + 0.01f, outlineColor);
	CCAGraphics::DrawRectangle(innerRect, depth, innerColor);
}

void OutlinedRectangle::SetPosition(Vector2D position)
{
	outlineRect.SetMinPosition(position);
	innerRect.SetMinPosition(position + Vector2D(1, 1));
}

void OutlinedRectangle::SetOutlineColor(u32 color)
{
	outlineColor = color;
}

void OutlinedRectangle::SetInnerColor(u32 color)
{
	innerColor = color;
}

void OutlinedRectangle::SetDepth(float depth)
{
	this->depth = depth;
}

const Rectangle& OutlinedRectangle::GetInnerRectangle() const
{
	return innerRect;
}

const Rectangle& OutlinedRectangle::GetOuterRectangle() const
{
	return outlineRect;
}