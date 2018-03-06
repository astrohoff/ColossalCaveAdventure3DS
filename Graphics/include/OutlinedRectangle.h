 #pragma once
 
 #include "CCAGraphics.h"
 
 class OutlinedRectangle
 {
	public:
		OutlinedRectangle();
		OutlinedRectangle(Rectangle area, float depth);
		void Draw() const;
		void SetPosition(Vector2D position);
		void SetOutlineColor(u32 color);
		void SetInnerColor(u32 color);
		void SetDepth(float depth);
		const Rectangle& GetInnerRectangle() const;
		const Rectangle& GetOuterRectangle() const;
		
	private:
		Rectangle outlineRect;
		Rectangle innerRect;
		u32 outlineColor;
		u32 innerColor;
		float depth;
 };