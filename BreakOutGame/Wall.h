#pragma once
#ifndef WALL_H_
#include "Object.h"

class Wall : public Object
{
	RECT rect;
public:
	Wall() : Object() 
	{
		objTag = WALL;
		rect = { 0,0,0,0 };
	}
	void SetWall(RECT rec)
	{
		width = rec.right;
		height = rec.bottom;
		objTag = WALL;
		rect = rec;
	}
	void Draw(HDC& hdc) override;
	void Update() override;
	RECT GetRect() const { return rect; }
};
#endif // !WALL_H_
