#include "WindowTab.h"

#define FONT_SIZE 0.6f

std::vector<WindowTab*> WindowTab::instances;

WindowTab::WindowTab()
{
	oRect = OutlinedRectangle(Rectangle(0, 35, 30, 26), 0.61f); 
}

WindowTab::WindowTab(std::string name, CommandGrid * commandGrid)
{
	uint instanceCount = WindowTab::instances.size();
	oRect = OutlinedRectangle(Rectangle(2+69*instanceCount, 35, 70, 26), 0.61f);	
	cmdGrid = commandGrid;
	label = GlyphGroup(name, oRect.GetInnerRectangle().GetMinPosition()+Vector2D(1,3), FONT_SIZE, 0.60f);
	instances.push_back(this);
	Deselect();
}

void WindowTab::Select()
{
	for(uint i = 0; i < WindowTab::instances.size(); i++)
	{
		WindowTab::instances[i]->Deselect();
	}
	oRect.SetInnerColor(0xC0C0C0FF);
	label.SetColor(0x000000FF);
	cmdGrid->isActive = true;
}

void WindowTab::Deselect()
{
	oRect.SetInnerColor(0x000000FF);
	label.SetColor(0xFFFFFFFF);
	cmdGrid->isActive = false;
}

void WindowTab::Draw() const
{
	oRect.Draw();
	label.Draw();
}

bool WindowTab::ContainsPoint(const Vector2D& point) const
{
	return oRect.GetOuterRectangle().Contains(point);
}