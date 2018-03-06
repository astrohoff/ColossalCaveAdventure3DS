#include "CommandTile.h"

CommandTile::CommandTile(std::string text, Vector2D homePosition)
{
	cmdText = text;
	this->homePosition = homePosition;
	oRect = OutlinedRectangle(Rectangle(homePosition, Vector2D(90, 30)), 0.81f);
	glyphGroup = GlyphGroup(text, Vector2D(0,0), 0.7f, 0.80f);
	
	textXPadding = (oRect.GetInnerRectangle().GetSize().x - glyphGroup.GetWidth()) / 2;
	glyphGroup.SetPosition(oRect.GetInnerRectangle().GetMinPosition() + Vector2D(textXPadding, 2));
	Release();
}

const std::string& CommandTile::GetCommand() const
{
	return cmdText;
}

void CommandTile::SetPosition(Vector2D position)
{
	oRect.SetPosition(position);
	glyphGroup.SetPosition(oRect.GetInnerRectangle().GetMinPosition() + Vector2D(textXPadding, 2));
}

void CommandTile::SetHomePosition(Vector2D position)
{
	homePosition = position;
}

void CommandTile::Draw() const
{
	oRect.Draw();
	glyphGroup.Draw();
}

bool CommandTile::ContainsPoint(const Vector2D& point) const
{
	return oRect.GetOuterRectangle().Contains(point);
}

Vector2D CommandTile::GetAnchorOffset(const Vector2D& anchorPos) const
{
	return oRect.GetOuterRectangle().GetMinPosition() - anchorPos;
}

void CommandTile::Grab()
{
	oRect.SetDepth(0.31f);
	oRect.SetInnerColor(0xD0D0D0FF);
	glyphGroup.SetDepth(0.30f);
	glyphGroup.SetColor(0x000000FF);
}

void CommandTile::Release()
{
	SetPosition(homePosition);
	oRect.SetDepth(0.81f);
	oRect.SetInnerColor(0x000000FF);
	glyphGroup.SetDepth(0.80f);
	glyphGroup.SetColor(0xFFFFFFFF);
}