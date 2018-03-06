#include "CommandGrid.h"

CommandGrid::CommandGrid()
{
}

void CommandGrid::SetCommands(const std::vector<std::string>& commands)
{
	cmdTiles.clear();
	Vector2D cmdTilePos = Vector2D(3, 63);
	float minX = cmdTilePos.x;
	uint cmdCount = commands.size();
	for(uint i = 0; i < cmdCount; i++)
	{
		cmdTiles.push_back(CommandTile(commands[i], cmdTilePos));
		cmdTilePos += Vector2D(95, 0);
		if(cmdTilePos.x + 90 > (317))
		{
			cmdTilePos.x = minX;
			cmdTilePos.y += 34;
		}
	}
}

void CommandGrid::Draw() const
{
	if(!isActive)
		return;
		
	uint cmdCount = cmdTiles.size();
	for(uint i = 0; i < cmdCount; i++)
	{
		cmdTiles[i].Draw();
	}
}

CommandTile * CommandGrid::GetCommandTileAtPoint(const Vector2D& point)
{
	if(!isActive)
		return nullptr;
		
	uint cmdCount = cmdTiles.size();
	for(uint i = 0; i < cmdCount; i++)
	{
		if(cmdTiles[i].ContainsPoint(point))
			return &cmdTiles[i];
	}
	return nullptr;
}