#include "TextPanel.h"

TextPanel::TextPanel()
{
	SetFontScale(0.8f);
}

TextPanel::TextPanel(float fontScale)
{
	SetFontScale(fontScale);
}

void TextPanel::SetFontScale(float scale)
{
	fontScale = scale;
	lineHeight = fontGetInfo()->lineFeed * scale;
}

void TextPanel::Draw() const
{
	uint lineCount = textLines.size();
	for(uint i = 0; i < lineCount; i++)
	{
		textLines[i].Draw();
	}
}

void TextPanel::AddLine(const std::string& line)
{
	textLines.push_back(GlyphGroup(line, Vector2D(0, lineHeight * textLines.size()), fontScale, 0.5f));
}