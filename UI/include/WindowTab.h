#pragma once

#include <string>
#include <vector>
#include "CommandGrid.h"
#include "OutlinedRectangle.h"
#include "GlyphGroup.h"

class WindowTab
{
	public:
		WindowTab();
		WindowTab(std::string name, CommandGrid * commandGrid);
		
		void Select();
		void Deselect();
		void Draw() const;
		bool ContainsPoint(const Vector2D& point) const;
		
	private:
		static std::vector<WindowTab*> instances;
		
		OutlinedRectangle oRect;
		GlyphGroup label;
		CommandGrid * cmdGrid;
};
