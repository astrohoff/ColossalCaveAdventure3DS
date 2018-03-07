#pragma once

#include <citro3d.h>
#include "Rectangle.h"
#include "CCAGraphics.h"

class TextureTile
{
	public:
		TextureTile();
		TextureTile(C3D_Tex * texture);
		TextureTile(C3D_Tex * texture, Rectangle positionRectangle, Rectangle uvRectangle, float depth, u32 color);
		
		const Rectangle& GetPositionRectangle() const;
		C3D_Tex * GetTexture() const;
		const Rectangle& GetUvRectangle() const;
		void SetPosition(Vector2D position);
		void Draw() const;
		void SetDepth(float depth);
		void SetColor(u32 color);
			
	private:
		Rectangle posRect;
		C3D_Tex * texture;
		Rectangle uvRect;
		float depth;
		u32 color;
};