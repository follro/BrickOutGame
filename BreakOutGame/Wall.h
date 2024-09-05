#pragma once
#ifndef WALL_H_
#include "Object.h"

class Wall : public Object
{
	RECT rect;
public:
	Wall() : Object() 
	{
		objTag = ObjectTag::WALL;
		rect = { 0,0,0,0 };
	}
	void SetWall(RECT rec)
	{
		width = rec.right;
		height = rec.bottom;
		objTag = ObjectTag::WALL;
		rect = rec;
	}
	void Draw(HDC& hdc) override;
	void Update() override;
	RECT GetRect() const { return rect; }
};
#endif // !WALL_H_
