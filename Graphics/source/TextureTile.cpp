#include "TextureTile.h"

TextureTile::TextureTile(){}

TextureTile::TextureTile(C3D_Tex * texture)
{
	this->texture = texture;
	posRect = Rectangle(0, 0, 50, 50);
	uvRect = Rectangle(0, 0, 1, 1);
}

TextureTile::TextureTile(C3D_Tex * texture, Rectangle positionRectangle, Rectangle uvRectangle)
{
	this->texture = texture;
	posRect = positionRectangle;
	uvRect = uvRectangle;
}

const Rectangle& TextureTile::GetPositionRectangle() const
{
	return posRect;
}

C3D_Tex * TextureTile::GetTexture() const
{
	return texture;
}

const Rectangle& TextureTile::GetUvRectangle() const
{
	return uvRect;
}

void TextureTile::SetPosition(Vector2D position)
{
	posRect.SetMinPosition(position);
}