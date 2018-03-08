#pragma once

#include <string>
#include <unordered_map>
#include <3ds.h>
#include <citro3d.h>
#include "TextureTile.h"

class TextHelper
{
	public:
		static float GetWidth(char c, float scale);
		static float GetWidth(const std::string& str, float scale);
		static Rectangle GetVertexRectangle(char c, float scale);
		static Rectangle GetUvRectangle(char c);
		static C3D_Tex* GetGlyphSheet(char c);
	
	private:
		static std::unordered_map<char,float> xAdvMap;
		static std::unordered_map<char,Rectangle> vtxMap;
		static std::unordered_map<char,Rectangle> uvMap;
		static std::unordered_map<char,C3D_Tex*> sheetMap;
		
		static void GetGlyphInfo(char c);
};