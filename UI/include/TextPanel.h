#pragma once

#include <vector>
#include <string>
#include <cctype>
#include <3ds.h>
#include "CCAGraphics.h"
#include "GlyphGroup.h"
#include "TextHelper.h"

class TextPanel
{
	public:
		TextPanel();
		TextPanel(float fontScale);
		
		void Draw() const;
		void SetFontScale(float scale);
		void AddLine(const std::string& line);
		void AddText(const std::string& text);
	
	private:
		std::vector<GlyphGroup> textLines;
		float fontScale;
		float lineHeight;
		Rectangle area;
		
		uint GetWrapIndex(const std::string& text) const;
		uint GetGroupStartIndex(const std::string& text, uint charIndex) const;
};