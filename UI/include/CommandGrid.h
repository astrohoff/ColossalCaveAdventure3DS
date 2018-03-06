#pragma once

#include <string>
#include <vector>
#include "CommandTile.h"
#include "CCAGraphics.h"

class CommandGrid
{
	public:
		bool isActive = false;
		
		CommandGrid();
		
		void SetCommands(const std::vector<std::string>& commands);
		void Draw() const;
		CommandTile * GetCommandTileAtPoint(const Vector2D& point);		
		
	private:
		std::vector<CommandTile> cmdTiles;
};