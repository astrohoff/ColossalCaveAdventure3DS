#pragma once

#include "OutlinedRectangle.h"
#include "TextureTile.h"
#include "CCAGraphics.h"
#include "Terminal.h"
#include "TextPanel.h"

class SubmitButton
{
	public:
		SubmitButton();
		SubmitButton(Terminal * terminal, TextPanel * textPanel);
		
		void Draw() const;
		void Press();
		void Release();
		bool ContainsPoint(const Vector2D& point) const;
	
	private:
		Terminal * terminal;
		TextPanel * textPanel;
		OutlinedRectangle oRect;
		TextureTile icon;
		bool pressed;
};