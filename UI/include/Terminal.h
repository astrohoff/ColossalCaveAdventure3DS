#pragma once

#include <string>
#include "OutlinedRectangle.h"
#include "GlyphGroup.h"

class Terminal
{
	public:
		Terminal();
		
		void Draw() const;
		bool ContainsPoint(const Vector2D& point) const;
		void AddCommand(const std::string& command);
		const std::string& GetText() const;
		void Clear();
	
	private:	
		OutlinedRectangle frame;
		GlyphGroup promptGlyph;
		GlyphGroup cmdGlyphs;
		std::string cmdString;
};