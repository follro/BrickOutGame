#pragma once
#ifndef PLATE_H_
#include "Object.h"
#include <cmath>
class Plate : public Object
{
public:
	enum class ItemState
	{
		NOTHING,LONG, SMALL, TRIPLE
	};
private:
	double movingSpeed;
	ItemState plateState;
	double PI;
	double angle = 90;
public:
	Plate(POINT _pos)
	{ 
		movingSpeed = 15;
		width = 200;
		height = 30;
		pos = _pos;
		plateState = ItemState::NOTHING;
		objTag = ObjectTag::PLATE;
		nomalVec = { 0,-1 };
		PI = std::acos(-1);
		SetVertex();
	}

	void SetPlateCenter(POINT center) { pos = center; }
	
	void Draw(HDC& hdc, HBRUSH& hBrush, HBRUSH& oldBrush) override;
	void Update() override;
	void Move(int way);
	void ChangeState(ItemState itemState);

};

#endif // !PLATE_H_
