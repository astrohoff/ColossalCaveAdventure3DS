#include "GlyphGroup.h"

GlyphGroup::GlyphGroup()
{
	text = "";
	position = Vector2D(0, 0);
}

GlyphGroup::GlyphGroup(std::string text, Vector2D position, float fontScale, float depth)
{
	this->text = "";
	this->position = position;
	this->fontScale = fontScale;
	this->depth = depth;
	color = 0xFFFFFFFF;
	AddText(text);
	//SetupGlyphs();
}

void GlyphGroup::SetupGlyphs()
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
		
		glyphTiles.push_back(TextureTile(glyphSheet, tileArea, uvRect, depth, color));
		
		tileOffset.x += glyphPosInfo.xAdvance;
	}
	tileOffsets.push_back(tileOffset);
}

void GlyphGroup::AddGlyph(char c)
{
	int fontGlyphIndex = fontGlyphIndexFromCodePoint(c);
	fontGlyphPos_s glyphPosInfo;
	fontCalcGlyphPos(&glyphPosInfo, fontGlyphIndex, GLYPH_POS_CALC_VTXCOORD, fontScale, fontScale);
	
	C3D_Tex * glyphSheet = &CCAGraphics::glyphSheets[glyphPosInfo.sheetIndex];
	
	Vector2D offset(glyphPosInfo.vtxcoord.left, glyphPosInfo.vtxcoord.top);
	if(tileOffsets.empty())
		tileOffsets.push_back(Vector2D(0, 0));
	offset.x += tileOffsets.back().x;
	tileOffsets.back() = offset;
	
	float tileSizeX = glyphPosInfo.vtxcoord.right - glyphPosInfo.vtxcoord.left;
	float tileSizeY = glyphPosInfo.vtxcoord.bottom - glyphPosInfo.vtxcoord.top;
	Rectangle tileArea = Rectangle(position + offset, Vector2D(tileSizeX, tileSizeY));
	
	Vector2D tileUvMin = Vector2D(glyphPosInfo.texcoord.left, glyphPosInfo.texcoord.top);
	Vector2D tileUvMax = Vector2D(glyphPosInfo.texcoord.right, glyphPosInfo.texcoord.bottom);
	Rectangle uvRect = Rectangle::ConstructMinMax(tileUvMin, tileUvMax);
	
	glyphTiles.push_back(TextureTile(glyphSheet, tileArea, uvRect, depth, color));
	
	offset.x += glyphPosInfo.xAdvance;
	tileOffsets.push_back(offset);
}

void GlyphGroup::AddText(const std::string& text)
{
	this->text += text;
	uint charCount = text.length();
	for(uint i = 0; i < charCount; i++)
	AddGlyph(text[i]);
}

void GlyphGroup::Draw() const
{
	uint glyphCount = glyphTiles.size();
	for(uint i = 0; i < glyphCount; i++)
	{
		glyphTiles[i].Draw();
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
	this->depth = depth;
	uint glyphCount = glyphTiles.size();
	for(uint i = 0; i < glyphCount; i++)
		glyphTiles[i].SetDepth(depth);
}

void GlyphGroup::SetColor(u32 colorRgba)
{
	this->color = colorRgba;
	uint glyphCount = glyphTiles.size();
	for(uint i = 0; i < glyphCount; i++)
		glyphTiles[i].SetColor(colorRgba);
}

const std::string& GlyphGroup::GetText() const
{
	return text;
}

float GlyphGroup::GetWidth() const
{
	return tileOffsets.back().x;
}

void GlyphGroup::Clear()
{
	glyphTiles.clear();
	tileOffsets.clear();
	text = "";
}