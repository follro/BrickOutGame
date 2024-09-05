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
		//width설정다시해야됨
		width = rec.right;
		height = rec.bottom;
		pos = { (rec.right - rec.left) / 2 , (rec.bottom - rec.top) / 2 };
		objTag = ObjectTag::WALL;
		rect = rec;
	}
	void Draw(HDC& hdc) override;
	void Update() override;
	RECT GetRect() const { return rect; }
};
#endif // !WALL_H_
