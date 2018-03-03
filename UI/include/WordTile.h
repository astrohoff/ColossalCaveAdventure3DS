#pragma once

#include <string>
#include <vector>
#include "Rectangle.h"
#include "CCAGraphics.h"
#include "TextureTile.h"

class WordTile
{
	public:	
		WordTile(std::string word);
		void SetPosition(const Vector2D& position);
		void Draw() const;
		bool ContainsPoint(const Vector2D& point) const;
		Vector2D GetAnchorOffset(const Vector2D& anchorPos) const;
		
	private:
		std::string word;
		Rectangle borderArea;
		Rectangle wordArea;
		std::vector<TextureTile> glyphTiles;
		std::vector<Vector2D> glyphTileOffsets;
		
		void SetupGlyphs();
};