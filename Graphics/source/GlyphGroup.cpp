#include "GlyphGroup.h"

GlyphGroup::GlyphGroup()
{
	text = "";
	position = Vector2D(0, 0);
	depth = 0.5f;
	color = 0xFFFFFFFF;
}

GlyphGroup::GlyphGroup(std::string text, Vector2D position, float fontScale, float depth)
{
	this->text = text;
	this->position = position;
	SetupGlyphs(fontScale);
	this->depth = depth;
	color = 0xFFFFFFFF;
}

void GlyphGroup::SetupGlyphs(float fontScale)
{
	Vector2D tileOffset = Vector2D(0, 0);
	uint charCount = text.size();
	for(uint i = 0; i < charCount; i++)
	{
		int fontGlyphIndex = fontGlyphIndexFromCodePoint((u32)text[i]);
		fontGlyphPos_s glyphPosInfo;
		fontCalcGlyphPos(&glyphPosInfo, fontGlyphIndex, GLYPH_POS_CALC_VTXCOORD, fontScale, fontScale);
		
		C3D_Tex * glyphSheet = &CCAGraphics::glyphSheets[glyphPosInfo.sheetIndex];
		
		tileOffset.y = glyphPosInfo.vtxcoord.top;
		tileOffset.x += glyphPosInfo.vtxcoord.left;
		tileOffsets.push_back(tileOffset);
		
		float tileSizeX = glyphPosInfo.vtxcoord.right - glyphPosInfo.vtxcoord.left;
		float tileSizeY = glyphPosInfo.vtxcoord.bottom - glyphPosInfo.vtxcoord.top;
		Rectangle tileArea = Rectangle(position + tileOffset, Vector2D(tileSizeX, tileSizeY));
		
		Vector2D tileUvMin = Vector2D(glyphPosInfo.texcoord.left, glyphPosInfo.texcoord.top);
		Vector2D tileUvMax = Vector2D(glyphPosInfo.texcoord.right, glyphPosInfo.texcoord.bottom);
		Rectangle uvRect = Rectangle::ConstructMinMax(tileUvMin, tileUvMax);
		
		glyphTiles.push_back(TextureTile(glyphSheet, tileArea, uvRect));
		
		tileOffset.x += glyphPosInfo.xAdvance;
	}
	tileOffsets.push_back(tileOffset);
}

void GlyphGroup::Draw() const
{
	uint glyphCount = glyphTiles.size();
	for(uint i = 0; i < glyphCount; i++)
	{
		CCAGraphics::DrawTexTile(glyphTiles[i], depth, color);
	}
}

void GlyphGroup::SetPosition(Vector2D position)
{
	this->position = position;
	uint glyphCount = glyphTiles.size();
	for(uint i = 0; i < glyphCount; i++)
	{
		glyphTiles[i].SetPosition(position + tileOffsets[i]);
	}
}

void GlyphGroup::SetDepth(float depth)
{
	this-> depth = depth;
}

void GlyphGroup::SetColor(u32 colorRgba)
{
	color = colorRgba;
}

const std::string& GlyphGroup::GetText() const
{
	return text;
}

float GlyphGroup::GetWidth() const
{
	return tileOffsets.back().x;
}