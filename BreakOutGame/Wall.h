#pragma once
#ifndef WALL_H_
#include "Object.h"

class Wall : public Object
{
	RECT rect;
public:
	Wall(RECT rec) : Object() 
	{
		width = rec.right;
		height = rec.bottom;
		pos = { (rec.right - rec.left) / 2 , (rec.bottom - rec.top) / 2 };
		objTag = ObjectTag::WALL;
		rect = rec;
	}
	void SetWall(RECT rec)
	{
		//width�����ٽ��ؾߵ�
		width = rec.right;
		height = rec.bottom;
		pos = { (rec.right - rec.left) / 2 , (rec.bottom - rec.top) / 2 };
		objTag = ObjectTag::WALL;
		rect = rec;
	}
	void Draw(HDC& hdc, HBRUSH& hBrush, HBRUSH& oldBrush) override;
	void Update() override;
	RECT GetRect() const { return rect; }
};
#endif // !WALL_H_
