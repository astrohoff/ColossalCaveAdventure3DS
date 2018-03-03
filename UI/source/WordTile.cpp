#include "WordTile.h"

#define FONT_SCALE 0.8f

WordTile::WordTile(std::string word)
{
	this->word = std::string(word);
	borderArea = Rectangle(0, 0, 100, 30);
	wordArea = Rectangle(1, 1, 98, 28);
	SetupGlyphs();
}

void WordTile::SetPosition(const Vector2D& position)
{
	borderArea.SetPosition(position);
	wordArea.SetPosition(position + Vector2D(1, 1));
	for(uint i = 0; i < glyphTiles.size(); i++)
	{
		glyphTiles[i].area.minPosition = wordArea.minPosition + glyphTileOffsets[i];
	}
}

void WordTile::Draw() const
{
	CCAGraphics::DrawRectangle(borderArea, 0.7f, 0xFFFFFFFF);
	CCAGraphics::DrawRectangle(wordArea, 0.6f, 0x000000FF);
	for(uint i = 0; i < glyphTiles.size(); i++)
	{
		CCAGraphics::DrawTexTile(glyphTiles[i], 0.5f, 0xFFFFFFFF);
	}
}

bool WordTile::ContainsPoint(const Vector2D& point) const
{
	return borderArea.Contains(point);
}

Vector2D WordTile::GetAnchorOffset(const Vector2D& anchorPos) const
{
	return borderArea.minPosition - anchorPos;
}

void WordTile::SetupGlyphs()
{
	Vector2D tileOffset = Vector2D(0, 0);
	for(uint i = 0; i < word.length(); i++)
	{
		int fontGlyphIndex = fontGlyphIndexFromCodePoint((u32)word[i]);
		fontGlyphPos_s glyphPosInfo;
		fontCalcGlyphPos(&glyphPosInfo, fontGlyphIndex, GLYPH_POS_CALC_VTXCOORD, FONT_SCALE, FONT_SCALE);
		C3D_Tex * glyphSheet = &CCAGraphics::glyphSheets[glyphPosInfo.sheetIndex];
		Vector2D glyphAreaMin = Vector2D(glyphPosInfo.vtxcoord.left, glyphPosInfo.vtxcoord.top);
		Vector2D glyphAreaMax = Vector2D(glyphPosInfo.vtxcoord.right, glyphPosInfo.vtxcoord.bottom);
		Rectangle glyphArea = Rectangle(glyphAreaMin, glyphAreaMax - glyphAreaMin);
		Vector2D glyphUvMin = Vector2D(glyphPosInfo.texcoord.left, glyphPosInfo.texcoord.top);
		Vector2D glyphUvMax = Vector2D(glyphPosInfo.texcoord.right, glyphPosInfo.texcoord.bottom);
		
		tileOffset.x += glyphAreaMin.x + glyphPosInfo.xAdvance;;
		tileOffset.y = glyphAreaMin.y;
		glyphTileOffsets.push_back(tileOffset);
		glyphArea.SetPosition(wordArea.minPosition + tileOffset);
		
		glyphTiles.push_back(TextureTile(glyphSheet, glyphArea, glyphUvMin, glyphUvMax));
	}
}