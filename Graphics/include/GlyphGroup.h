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
		void Draw(const Rectangle& clipRect) const;
		void AddText(const std::string& text);
		void Clear();
	
	private:
		std::string text;
		Vector2D position;
		float fontScale;
		float depth;
		u32 color;
		std::vector<TextureTile> glyphTiles;
		std::vector<Vector2D> tileOffsets;
		
		void SetupGlyphs();
		void AddGlyph(char c);
};