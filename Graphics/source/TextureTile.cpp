#include "TextureTile.h"

TextureTile::TextureTile(){}

TextureTile::TextureTile(C3D_Tex * texture)
{
	this->texture = texture;
	posRect = Rectangle(0, 0, 50, 50);
	uvRect = Rectangle(0, 0, 1, 1);
}

TextureTile::TextureTile(C3D_Tex * texture, Rectangle positionRectangle, Rectangle uvRectangle, float depth, u32 color)
{
	this->texture = texture;
	posRect = positionRectangle;
	uvRect = uvRectangle;
	this->depth = depth;
	this->color = color;
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

void TextureTile::Draw() const
{
	CCAGraphics::DrawTexture(texture, posRect, uvRect, depth, color);
}

void TextureTile::SetDepth(float depth)
{
	this->depth = depth;
}

void TextureTile::SetColor(u32 color)
{
	this->color = color;
}