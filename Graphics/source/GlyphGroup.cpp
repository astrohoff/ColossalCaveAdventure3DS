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
}

void GlyphGroup::AddGlyph(char c)
{	
	C3D_Tex * glyphSheet = TextHelper::GetGlyphSheet(c);
	
	Rectangle tileArea = TextHelper::GetVertexRectangle(c, fontScale);
	Vector2D offset = tileArea.GetMinPosition();
	if(tileOffsets.empty())
		tileOffsets.push_back(Vector2D(0, 0));
	offset.x += tileOffsets.back().x;
	tileOffsets.back() = offset;
	tileArea.SetMinPosition(offset + position);
	
	Rectangle uvRect = TextHelper::GetUvRectangle(c);
	
	glyphTiles.push_back(TextureTile(glyphSheet, tileArea, uvRect, depth, color));
	
	offset.x += TextHelper::GetWidth(c, fontScale);
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