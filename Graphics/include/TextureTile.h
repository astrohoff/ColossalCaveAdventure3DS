#pragma once

#include <citro3d.h>
#include "Rectangle.h"

class TextureTile
{
	public:
		TextureTile();
		TextureTile(C3D_Tex * texture);
		TextureTile(C3D_Tex * texture, Rectangle positionRectangle, Rectangle uvRectangle);
		
		const Rectangle& GetPositionRectangle() const;
		C3D_Tex * GetTexture() const;
		const Rectangle& GetUvRectangle() const;
		void SetPosition(Vector2D position);
			
	private:
		Rectangle posRect;
		C3D_Tex * texture;
		Rectangle uvRect;	
};