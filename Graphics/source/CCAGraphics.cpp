#include "CCAGraphics.h"

#define CLEAR_COLOR 0x000000FF

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))
	
#define TOP_SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240
#define BOT_SCREEN_WIDTH 320

u32 CCAGraphics::currentDrawColor = 0x000000FF;
C3D_Tex * CCAGraphics::currentTexture;
CCAGraphics::ColorMode CCAGraphics::currentColorMode = ColorMode::Unknown;
bool CCAGraphics::midDraw = false;
DVLB_s * CCAGraphics::vshader_dvlb;
shaderProgram_s CCAGraphics::shader_program;
// Location of shader projection uniform (global variable).
int CCAGraphics::uLoc_projection;
// Top and bottom screen projection matrices.
C3D_Mtx CCAGraphics::projectionTop;
C3D_Mtx CCAGraphics::projectionBottom;
CCAGraphics::RenderScreen CCAGraphics::currentScreen = RenderScreen::Unknown;
C3D_RenderTarget * CCAGraphics::topRendTarg;
C3D_RenderTarget * CCAGraphics::bottomRendTarg;
C3D_Tex * CCAGraphics::glyphSheets;

	
// Configures current shader for textured or untextured coloring.
void CCAGraphics::ConfigureColorMode(ColorMode colorMode)
{
	if(colorMode == currentColorMode)
		return;
	
	EndDraw();
	
	// GPU values we need that depend on whether textures are being used.
	GPU_TEVSRC alphaSrc1;
	GPU_TEVSRC alphaSrc2;
	GPU_COMBINEFUNC alphaCombine;
	// Set these value appropriately.
	if (colorMode == ColorMode::Textured) {
		// Values taken from devkitPro system font example.
		// Guessing this says to take the texture alpha and color alpha
		// and mutliply them.
		alphaSrc1 = GPU_TEXTURE0;
		alphaSrc2 = GPU_CONSTANT;
		alphaCombine = GPU_MODULATE;
	}
	else {
		// Values taken from devkitPro simple tri example.
		// Guessing this says to just use the color alpha.
		alphaSrc1 = GPU_CONSTANT;
		// This is just the default value for this parameter.
		alphaSrc2 = GPU_PRIMARY_COLOR;
		alphaCombine = GPU_REPLACE;
	}

	// Configure shader with above dependent values + independent ones.
	C3D_TexEnv* texEnv = C3D_GetTexEnv(0);
	// Set color and alpha sources.
	C3D_TexEnvSrc(texEnv, C3D_RGB, GPU_CONSTANT, 0, 0);
	C3D_TexEnvSrc(texEnv, C3D_Alpha, alphaSrc1, alphaSrc2, 0);
	// Use default combine operands.
	C3D_TexEnvOp(texEnv, C3D_Both, 0, 0, 0);
	// Set color and alpha combine functions.
	C3D_TexEnvFunc(texEnv, C3D_RGB, GPU_REPLACE);
	C3D_TexEnvFunc(texEnv, C3D_Alpha, alphaCombine);
	
	currentColorMode = colorMode;
}

void CCAGraphics::StartDraw()
{
	if(midDraw)
		EndDraw();
	midDraw = true;
	C3D_ImmDrawBegin(GPU_TRIANGLE_FAN);
}

void CCAGraphics::EndDraw()
{
	if(midDraw)
	{
		midDraw = false;
		C3D_ImmDrawEnd();
	}
}

void CCAGraphics::EnsureDrawing()
{
	if(!midDraw)
		StartDraw();
}

void CCAGraphics::FrameStart()
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	SetRenderScreen(currentScreen, true);
}

void CCAGraphics::FrameStart(RenderScreen screen)
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	SetRenderScreen(screen, true);
}

void CCAGraphics::FrameEnd()
{
	EndDraw();
	C3D_FrameEnd(0);
}

void CCAGraphics::DrawRectInternal(const Rectangle& rect, float depth, bool updateColorMode)
{
	if(updateColorMode)
		ConfigureColorMode(ColorMode::Untextured);
	EnsureDrawing();
	
	const Vector2D& minPos = rect.GetMinPosition();
	const Vector2D& maxPos = rect.GetMaxPosition();
	// Set a vertex position, then set anything for the unused texture coordinate attribute.
	// Triangle fan.
	C3D_ImmSendAttrib(minPos.x, minPos.y, depth, 0);
	C3D_ImmSendAttrib(0, 0, 0, 0);
	C3D_ImmSendAttrib(minPos.x, maxPos.y, depth, 0);
	C3D_ImmSendAttrib(0, 0, 0, 0);
	C3D_ImmSendAttrib(maxPos.x, maxPos.y, depth, 0);
	C3D_ImmSendAttrib(0, 0, 0, 0);
	C3D_ImmSendAttrib(maxPos.x, minPos.y, depth, 0);
	C3D_ImmSendAttrib(0, 0, 0, 0);
	C3D_ImmDrawRestartPrim();
}

void CCAGraphics::SetTexture(C3D_Tex * texture)
{
	if(texture != currentTexture)
	{		
		EndDraw();
		C3D_TexBind(0, texture);
		currentTexture = texture;
	}
}

void CCAGraphics::Init()
{	
	// Initialize graphics
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	// Setup top screen render target.
	topRendTarg = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetClear(topRendTarg, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
	C3D_RenderTargetSetOutput(topRendTarg, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
	// Setup bottom screen render target.
	bottomRendTarg = C3D_RenderTargetCreate(240, 320, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetClear(bottomRendTarg, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
	C3D_RenderTargetSetOutput(bottomRendTarg, GFX_BOTTOM, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
	
	// Load the vertex shader, create a shader program and bind it.
	vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin, vshader_shbin_size);
	shaderProgramInit(&shader_program);
	shaderProgramSetVsh(&shader_program, &vshader_dvlb->DVLE[0]);
	C3D_BindProgram(&shader_program);

	// Get the location of the uniforms.
	uLoc_projection = shaderInstanceGetUniformLocation(shader_program.vertexShader, "projection");

	// Configure attributes for use with the vertex shader.
	// Attribute format and element count are ignored in immediate mode.
	C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
	AttrInfo_Init(attrInfo);
	// v0=position.
	AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3);
	// v1=texcoord.
	AttrInfo_AddLoader(attrInfo, 1, GPU_FLOAT, 2);

	// Compute the top & bottom screen projection matrices.
	Mtx_OrthoTilt(&projectionTop, 0, 400.0f, 240.0f, 0.0f, 0.0f, 1.0f, true);
	Mtx_OrthoTilt(&projectionBottom, 0, 320.0f, 240.0f, 0.0f, 0.0f, 1.0f, true);
	
	// Load glyph texture sheets.
	fontEnsureMapped();
	TGLP_s* glyphsInfo = fontGetGlyphInfo();
	// Allocate memory for glyph textures.
	glyphSheets = new C3D_Tex[glyphsInfo->nSheets];
	// Load glyph textures.
	for (int i = 0; i < glyphsInfo->nSheets; i++)
	{
		C3D_Tex* tex = &glyphSheets[i];
		tex->data = fontGetGlyphSheetTex(i);
		tex->fmt = static_cast<GPU_TEXCOLOR>(glyphsInfo->sheetFmt);
		tex->size = glyphsInfo->sheetSize;
		tex->width = glyphsInfo->sheetWidth;
		tex->height = glyphsInfo->sheetHeight;
		tex->param = GPU_TEXTURE_MAG_FILTER(GPU_LINEAR) | GPU_TEXTURE_MIN_FILTER(GPU_LINEAR)
			| GPU_TEXTURE_WRAP_S(GPU_CLAMP_TO_EDGE) | GPU_TEXTURE_WRAP_T(GPU_CLAMP_TO_EDGE);
		tex->border = 0;
		tex->lodParam = 0;
	}
	
	ConfigureColorMode(ColorMode::Untextured);
	SetDrawColor(currentDrawColor);
	SetRenderScreen(RenderScreen::Top, false);
}

void CCAGraphics::Deinit()
{
	free(glyphSheets);
	shaderProgramFree(&shader_program);
	DVLB_Free(vshader_dvlb);
	C3D_Fini();
	gfxExit();
}

void CCAGraphics::SetDrawColor(u32 colorRgba)
{
	if(colorRgba != currentDrawColor)
	{
		u32 colorAbgr = ((colorRgba & 0x000000FF) << 24) | ((colorRgba & 0x0000FF00) << 8) |
						((colorRgba & 0x00FF0000) >> 8) | ((colorRgba & 0xFF000000) >> 24);
		
		EndDraw();
		C3D_TexEnv* texEnv = C3D_GetTexEnv(0);
		C3D_TexEnvColor(texEnv, colorAbgr);
		currentDrawColor = colorRgba;
	}	
}

void CCAGraphics::SetRenderScreen(RenderScreen screen, bool forceSet)
{
	if(screen != currentScreen || forceSet)
	{
		currentScreen = screen;
		if(screen == RenderScreen::Top)
		{
			C3D_FrameDrawOn(topRendTarg);
			C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projectionTop);
		}
		else
		{
			C3D_FrameDrawOn(bottomRendTarg);
			C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projectionBottom);
		}
	}
}

void CCAGraphics::DrawRectangle(const Rectangle& rect, float depth)
{
	DrawRectInternal(rect, depth, true);
}

void CCAGraphics::DrawRectangle(const Rectangle& rect, float depth, u32 colorRgba)
{
	ConfigureColorMode(ColorMode::Untextured);
	SetDrawColor(colorRgba);
	DrawRectInternal(rect, depth, false);
}

void CCAGraphics::DrawTexture(C3D_Tex * tex, const Rectangle& posRect, const Rectangle& uvRect, float depth, u32 colorRgba)
{
	ConfigureColorMode(ColorMode::Textured);
	SetDrawColor(colorRgba);
	SetTexture(tex);
	EnsureDrawing();
	
	const Vector2D& posMin = posRect.GetMinPosition();
	Vector2D posMax = posRect.GetMaxPosition();
	const Vector2D& uvMin = uvRect.GetMinPosition();
	Vector2D uvMax = uvRect.GetMaxPosition();
	
	C3D_ImmSendAttrib(posMin.x, posMin.y, depth, 0);
	C3D_ImmSendAttrib(uvMin.x, uvMin.y, 0, 0);
	C3D_ImmSendAttrib(posMin.x, posMax.y, depth, 0);
	C3D_ImmSendAttrib(uvMin.x, uvMax.y, 0, 0);
	C3D_ImmSendAttrib(posMax.x, posMax.y, depth, 0);
	C3D_ImmSendAttrib(uvMax.x, uvMax.y, 0, 0);
	C3D_ImmSendAttrib(posMax.x, posMin.y, depth, 0);
	C3D_ImmSendAttrib(uvMax.x, uvMin.y, 0, 0);
	C3D_ImmDrawRestartPrim();
}