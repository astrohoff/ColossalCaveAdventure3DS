#include <3ds.h>
#include <citro3d.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "CCAGraphics.h"
#include "Rectangle.h"
#include "CommandTile.h"
#include "GlyphGroup.h"
#include "OutlinedRectangle.h"
#include "CommandGrid.h"
#include "WindowTab.h"
#include "Terminal.h"
#include "SubmitButton.h"

#define CMD_CAT_CNT		2

int main(){
	CCAGraphics::Init();
	
	touchPosition rawTouchPos;
	
	OutlinedRectangle mainFrame(Rectangle(0, 60, 320, 240-60), 0.9f);
	Terminal terminal;
	SubmitButton submitButton(&terminal);
	
	CommandGrid movesGrid;
	CommandGrid nounsGrid;
	
	std::string cmdArray1[] = {"road","enter","up","down","forrest",
								"forward","back","valley"};
	std::string cmdArray2[] = {"stairs","out", "house","gully","stream","fork"};
	std::vector<std::string> cmdVect1(std::begin(cmdArray1), std::end(cmdArray1));
	std::vector<std::string> cmdVect2(std::begin(cmdArray2), std::end(cmdArray2));
	movesGrid.SetCommands(cmdVect1);
	nounsGrid.SetCommands(cmdVect2);
	
	CommandGrid * cmdGrids[CMD_CAT_CNT] = {&movesGrid, &nounsGrid};
	
	WindowTab movesTab("Moves", &movesGrid);
	WindowTab nounsTab("Nouns", &nounsGrid);
	WindowTab * winTabs[CMD_CAT_CNT] = { &movesTab, &nounsTab };
	
	movesTab.Select();
	
	bool touching = false;
	bool tapping = false;
	bool releasing = false;
	
	CommandTile * grabbedCmd = nullptr;
	Vector2D cmdGrabOffset;
	
	Vector2D touchPosV2D(0,0);
	Vector2D prevTouchPosV2D(0,0);
	
	while(aptMainLoop())
	{
		prevTouchPosV2D = touchPosV2D;
		hidScanInput();
		hidTouchRead(&rawTouchPos);
		touchPosV2D = Vector2D(rawTouchPos.px, rawTouchPos.py);
		
		if(hidKeysDown() & KEY_START)
			break;
		
		// Determine touch state.
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
		
		// Check if something is being tapped.
		if(tapping)
		{
			if(mainFrame.GetOuterRectangle().Contains(touchPosV2D))
			{	
				for(int i = 0; i < CMD_CAT_CNT && grabbedCmd == nullptr; i++)
				{
					grabbedCmd = cmdGrids[i]->GetCommandTileAtPoint(touchPosV2D);
					if(grabbedCmd != nullptr)
					{
						cmdGrabOffset = grabbedCmd->GetAnchorOffset(touchPosV2D);
						grabbedCmd->Grab();
					}
				}
			}
			else
			{
				bool tabHit = false;
				for(int i = 0; i < CMD_CAT_CNT && !tabHit; i++)
				{
					if(winTabs[i]->ContainsPoint(touchPosV2D))
					{
						winTabs[i]->Select();
						tabHit = true;
					}
				}
				if(submitButton.ContainsPoint(touchPosV2D))
					submitButton.Press();
			}
		}
		else if(releasing)
		{
			if(grabbedCmd != nullptr)
			{
				if(terminal.ContainsPoint(prevTouchPosV2D))
				{
					terminal.AddCommand(grabbedCmd->GetCommand());
				}
				grabbedCmd->Release();
				grabbedCmd = nullptr;
			}
			submitButton.Release();
		}
		
		if(grabbedCmd != nullptr)
		{
			grabbedCmd->SetPosition(touchPosV2D + cmdGrabOffset);
		}
		
			
		CCAGraphics::FrameStart(CCAGraphics::RenderScreen::Bottom);
		
		mainFrame.Draw();
		terminal.Draw();
		submitButton.Draw();
		
		for(int i = 0; i < CMD_CAT_CNT; i++)
		{
			winTabs[i]->Draw();
			cmdGrids[i]->Draw();
		}
		
		CCAGraphics::FrameEnd();
	}
	
	CCAGraphics::Deinit();
	return 0;
}