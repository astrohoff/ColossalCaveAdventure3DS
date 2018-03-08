#include "TextHelper.h"

std::unordered_map<char,float> TextHelper::xAdvMap;
std::unordered_map<char,Rectangle> TextHelper::vtxMap;
std::unordered_map<char,Rectangle> TextHelper::uvMap;
std::unordered_map<char,C3D_Tex*> TextHelper::sheetMap;

float TextHelper::GetWidth(char c, float scale)
{
	if(xAdvMap.count(c) == 0)
		TextHelper::GetGlyphInfo(c);
	return TextHelper::xAdvMap[c] * scale;
}

float TextHelper::GetWidth(const std::string& str, float scale)
{
	float width = 0;
	uint charCount = str.length();
	for(uint i = 0; i < charCount; i++)
	{
		width += TextHelper::GetWidth(str[i], scale);
	}
	return width;
}

Rectangle TextHelper::GetVertexRectangle(char c, float scale)
{
	if(vtxMap.count(c) == 0)
		GetGlyphInfo(c);
	Rectangle temp = vtxMap[c];
	temp.Scale(scale, Rectangle::ScaleOrigin::MinPosition);
	return temp;
}

Rectangle TextHelper::GetUvRectangle(char c)
{
	if(uvMap.count(c) == 0)
		GetGlyphInfo(c);
	return uvMap[c];
}

C3D_Tex* TextHelper::GetGlyphSheet(char c)
{
	if(sheetMap.count(c) == 0)
		GetGlyphInfo(c);
	return sheetMap[c];
}

void TextHelper::GetGlyphInfo(char c)
{		
	int fontGlyphIndex = fontGlyphIndexFromCodePoint(c);
	fontGlyphPos_s glyphPosInfo;
	fontCalcGlyphPos(&glyphPosInfo, fontGlyphIndex, GLYPH_POS_CALC_VTXCOORD, 1, 1);
	
	C3D_Tex * glyphSheet = &CCAGraphics::glyphSheets[glyphPosInfo.sheetIndex];
	
	Vector2D pos(glyphPosInfo.vtxcoord.left, glyphPosInfo.vtxcoord.top);	
	float tileSizeX = glyphPosInfo.vtxcoord.right - glyphPosInfo.vtxcoord.left;
	float tileSizeY = glyphPosInfo.vtxcoord.bottom - glyphPosInfo.vtxcoord.top;
	Rectangle tileArea = Rectangle(pos, Vector2D(tileSizeX, tileSizeY));
	
	Vector2D tileUvMin = Vector2D(glyphPosInfo.texcoord.left, glyphPosInfo.texcoord.top);
	Vector2D tileUvMax = Vector2D(glyphPosInfo.texcoord.right, glyphPosInfo.texcoord.bottom);
	Rectangle uvRect = Rectangle::ConstructMinMax(tileUvMin, tileUvMax);
	
	xAdvMap[c] = glyphPosInfo.xAdvance;
	vtxMap[c] = tileArea;
	uvMap[c] = uvRect;
	sheetMap[c] = glyphSheet;
}