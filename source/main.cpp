#include <3ds.h>
#include <citro3d.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "CCAGraphics.h"
#include "Rectangle.h"
#include "WordTile.h"

int main(){
	CCAGraphics::Init();
	touchPosition rawTouchPos;
	
	WordTile testWTile = WordTile("north");
	
	bool touching = false;
	bool tapping = false;
	bool releasing = false;
	
	bool grabbing = false;
	Vector2D grabTileOffset;
	
	while(aptMainLoop())
	{
		hidScanInput();
		hidTouchRead(&rawTouchPos);
		Vector2D touchPosV2D = Vector2D(rawTouchPos.px, rawTouchPos.py);
		
		if(hidKeysDown() & KEY_START)
			break;
		
		if(touchPosV2D != Vector2D(0, 0))
		{
			tapping = !touching;
			releasing = false;
			touching = true;
		}
		else
		{
			tapping = false;
			releasing = touching;
			touching = false;
		}
		
		if(tapping && testWTile.ContainsPoint(touchPosV2D))
		{
			grabbing = true;
			grabTileOffset = testWTile.GetAnchorOffset(touchPosV2D);
		}
		else if(releasing)
			grabbing = false;
		
		if(grabbing)
		{
			testWTile.SetPosition(touchPosV2D + grabTileOffset);
		}
			
		CCAGraphics::FrameStart(CCAGraphics::RenderScreen::Bottom);
		
		testWTile.Draw();
		
		CCAGraphics::FrameEnd();
	}
	CCAGraphics::Deinit();
	return 0;
}