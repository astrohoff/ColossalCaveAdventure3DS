#pragma once

#include <string>
#include <vector>
#include "CCAGraphics.h"

class GlyphGroup
{
	public:
		GlyphGroup();
		GlyphGroup(std::string text, Vector2D position, float fontScale, float depth);
		
		void SetPosition(Vector2D position);
		void SetDepth(float depth);
		void SetColor(u32 colorRgba);
		const std::string& GetText() const;
		float GetWidth() const;
		void Draw() const;
		
	
	private:
		std::string text;
		Vector2D position;
		std::vector<TextureTile> glyphTiles;
		std::vector<Vector2D> tileOffsets;
		float depth;
		u32 color;
		
		void SetupGlyphs(float fontScale);
};