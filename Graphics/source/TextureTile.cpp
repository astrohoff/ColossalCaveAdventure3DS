#include "TextureTile.h"

TextureTile::TextureTile(C3D_Tex * texture)
{
	this->texture = texture;
	area = Rectangle(0, 0, 50, 50);
	uvMin = Vector2D(0, 0);
	uvMax = Vector2D(1, 1);
}

TextureTile::TextureTile(C3D_Tex * texture, Rectangle area, Vector2D uvMin, Vector2D uvMax)
{
	this->texture = texture;
	this->area = area;
	this->uvMin = uvMin;
	this->uvMax = uvMax;
}