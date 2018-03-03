#pragma once
#include <3ds.h>
#include <citro3d.h>
#include <stdlib.h>

#include "vshader_shbin.h"
#include "Rectangle.h"
#include "TextureTile.h"

class CCAGraphics
{
	public:
		enum class RenderScreen { Top, Bottom, Unknown };
		static C3D_Tex * glyphSheets;
		
		static void Init();
		static void Deinit();
		static void SetDrawColor(u32 colorRgba);
		static void SetRenderScreen(RenderScreen screen, bool forceSet);
		static void DrawRectangle(const Rectangle& rect, float depth);
		static void DrawRectangle(const Rectangle& rect, float depth, u32 colorRgba);
		static void DrawTexTile(const TextureTile& texTile, float depth, u32 colorRgba);
		static void FrameStart();
		static void FrameStart(RenderScreen screen);
		static void FrameEnd();
		
		
	private:
		static u32 currentDrawColor;
		static C3D_Tex * currentTexture;
		enum class ColorMode { Untextured, Textured, Unknown };
		static ColorMode currentColorMode;
		static bool midDraw;
		static DVLB_s * vshader_dvlb;
		static shaderProgram_s shader_program;
		// Location of shader projection uniform (global variable).
		static int uLoc_projection;
		// Top and bottom screen projection matrices.
		static C3D_Mtx projectionTop, projectionBottom;
		static RenderScreen currentScreen;
		static C3D_RenderTarget * topRendTarg, * bottomRendTarg;
		
		static void EndDraw();
		static void ConfigureColorMode(ColorMode colorMode);
		static void StartDraw();
		static void EnsureDrawing();
		static void DrawRectInternal(const Rectangle& rect, float depth, bool setColorMode);
		static void SetTexture(C3D_Tex * texture);
};