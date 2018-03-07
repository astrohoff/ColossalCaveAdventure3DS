#include "Terminal.h"

Terminal::Terminal()
{
	frame = OutlinedRectangle(Rectangle(0, 0, 220, 30), 0.91f);
	promptGlyph = GlyphGroup(">", Vector2D(3, 2), 0.8f, 0.90f);
	cmdGlyphs = GlyphGroup("", Vector2D(30, 4), 0.7f, 0.90f);
}


void Terminal::Draw() const
{
	frame.Draw();
	promptGlyph.Draw();
	cmdGlyphs.Draw();
}

bool Terminal::ContainsPoint(const Vector2D& point) const
{
	return frame.GetOuterRectangle().Contains(point);
}

void Terminal::AddCommand(const std::string& cmdString)
{
	if(cmdGlyphs.GetText().length() > 0)
		cmdGlyphs.AddText(" ");
	cmdGlyphs.AddText(cmdString);
}

const std::string& Terminal::GetText() const
{
	return cmdGlyphs.GetText();
}

void Terminal::Clear()
{
	cmdGlyphs.Clear();
}