#pragma once

#include <vector>
#include <string>
#include <3ds.h>
#include "CCAGraphics.h"
#include "GlyphGroup.h"

class TextPanel
{
	public:
		TextPanel();
		TextPanel(float fontScale);
		
		void Draw() const;
		void SetFontScale(float scale);
		void AddLine(const std::string& line);
	
	private:
		std::vector<GlyphGroup> textLines;
		float fontScale;
		float lineHeight;
};