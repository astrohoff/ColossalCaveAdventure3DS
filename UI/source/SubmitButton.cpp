#include "SubmitButton.h"

SubmitButton::SubmitButton()
{
}

SubmitButton::SubmitButton(Terminal * terminal)
{
	this->terminal = terminal;
	oRect = OutlinedRectangle(Rectangle(223, 0, 30, 30), 0.91f);
	
	int fontGlyphIndex = fontGlyphIndexFromCodePoint(0x2191);
	fontGlyphPos_s glyphPosInfo;
	fontCalcGlyphPos(&glyphPosInfo, fontGlyphIndex, GLYPH_POS_CALC_VTXCOORD, .8f, .8f);	
	
	C3D_Tex * glyphSheet = &CCAGraphics::glyphSheets[glyphPosInfo.sheetIndex];	
	
	float tileSizeX = glyphPosInfo.vtxcoord.right - glyphPosInfo.vtxcoord.left;
	float tileSizeY = glyphPosInfo.vtxcoord.bottom - glyphPosInfo.vtxcoord.top;
	
	Rectangle tileArea = Rectangle(Vector2D(224+(28-tileSizeX)/2, 1+(28-tileSizeY)/2), Vector2D(tileSizeX, tileSizeY));
	
	Vector2D tileUvMin = Vector2D(glyphPosInfo.texcoord.left, glyphPosInfo.texcoord.top);
	Vector2D tileUvMax = Vector2D(glyphPosInfo.texcoord.right, glyphPosInfo.texcoord.bottom);
	Rectangle uvRect = Rectangle::ConstructMinMax(tileUvMin, tileUvMax);
	
	icon = TextureTile(glyphSheet, tileArea, uvRect);
	pressed = false;
}

void SubmitButton::Draw() const
{
	oRect.Draw();
	if(pressed)
		CCAGraphics::DrawTexTile(icon, 0.90f, 0x000000FF);
	else
		CCAGraphics::DrawTexTile(icon, 0.90f, 0xFFFFFFFF);
}

void SubmitButton::Press()
{
	pressed = true;
	oRect.SetInnerColor(0xC0C0C0FF);
	terminal->Clear();
}

void SubmitButton::Release()
{
	pressed = false;
	oRect.SetInnerColor(0x000000FF);
}

bool SubmitButton::ContainsPoint(const Vector2D& point) const
{
	return oRect.GetOuterRectangle().Contains(point);
}