#pragma once

#include <string>
#include <vector>
#include "CCAGraphics.h"
#include "GlyphGroup.h"
#include "OutlinedRectangle.h"

class CommandTile
{
	public:	
		CommandTile(std::string text, Vector2D homePosition);
		
		const std::string& GetCommand() const;
		void SetPosition(Vector2D position);
		void SetHomePosition(Vector2D position);
		
		void Draw() const;
		bool ContainsPoint(const Vector2D& point) const;
		Vector2D GetAnchorOffset(const Vector2D& anchorPos) const;
		void Grab();
		void Release();
		
		
	private:
		std::string cmdText;
		Vector2D homePosition;
		OutlinedRectangle oRect;
		GlyphGroup glyphGroup;
		float textXPadding;
};