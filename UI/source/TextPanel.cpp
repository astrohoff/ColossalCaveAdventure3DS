#include "TextPanel.h"

TextPanel::TextPanel()
{
	SetFontScale(0.8f);
	area = Rectangle(0, 0, 370, 240);
}

TextPanel::TextPanel(float fontScale)
{
	area = Rectangle(0, 0, 370, 240);
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

void TextPanel::AddText(const std::string& text)
{
	AddLine(text);
}

uint TextPanel::GetWrapIndex(const std::string& text) const
{
	float width = 0;
	float xLimit = area.GetMaxPosition().x;
	uint charCount = text.length();
	for(uint i = 0; i < charCount; i++)
	{
		width += TextHelper::GetWidth(text[i], fontScale);
		if(width >= xLimit)
			return i;
	}
	return -1;
}

uint TextPanel::GetGroupStartIndex(const std::string& text, uint charIndex) const
{
	uint groupStartIndex = charIndex;
	if(isspace(text[groupStartIndex]))
	{
		while((groupStartIndex - 1 >= 0) && isspace(text[groupStartIndex - 1]))
			groupStartIndex--;
	}
	else
	{
		while((groupStartIndex - 1 >= 0) && isgraph(text[groupStartIndex - 1]))
			groupStartIndex--;
	}
	return groupStartIndex;
}