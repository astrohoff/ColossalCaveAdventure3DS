#include "Terminal.h"

Terminal::Terminal()
{
	frame = OutlinedRectangle(Rectangle(0, 0, 220, 30), 0.91f);
	promptGlyph = GlyphGroup(">", Vector2D(3, 2), 0.8f, 0.90f);
	cmdString = "";
}


void Terminal::Draw() const
{
	frame.Draw();
	promptGlyph.Draw();
	if(cmdString.size() > 0)
		cmdGlyphs.Draw();
}

bool Terminal::ContainsPoint(const Vector2D& point) const
{
	return frame.GetOuterRectangle().Contains(point);
}

void Terminal::AddCommand(const std::string& cmdString)
{
	if(this->cmdString.size() > 0)
		this->cmdString.append(" ");
	this->cmdString.append(cmdString);
	cmdGlyphs = GlyphGroup(this->cmdString, Vector2D(30, 4), 0.7f, 0.90f);
}

const std::string& Terminal::GetText() const
{
	return cmdString;
}

void Terminal::Clear()
{
	cmdString = "";
}