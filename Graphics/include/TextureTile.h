#pragma once

#include <citro3d.h>
#include "Rectangle.h"

class TextureTile
{
	public:
		Rectangle area;
		C3D_Tex * texture;
		Vector2D uvMin, uvMax;
		
		TextureTile(C3D_Tex * texture);
		TextureTile(C3D_Tex * texture, Rectangle area, Vector2D uvMin, Vector2D uvMax);
			
	private:
		
};