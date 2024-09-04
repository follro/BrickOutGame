#pragma once
#ifndef PLATE_H_
#include "Object.h"
#include <cmath>
class Plate : public Object
{
	enum ItemState
	{
		sNOTHING,sLONG, sSMALL, sTRIPLE
	};
	double movingSpeed;
	ItemState plateState;
	double PI;
	double angle = 90;
public:
	Plate()
	{ 
		movingSpeed = 15;
		width = 200;
		height = 40; 
		pos = { 0, 0 }; 
		plateState = sNOTHING;
		objTag = PLATE;
		nomalVec = { 0,1 };
		PI = std::acos(-1);
	}

	void SetPlateCenter(POINT center) { pos = center; }
	
	void Draw(HDC& hdc) override;
	void Update() override;
	void Move(int way);
	void ChangeState(int itemState);

};

#endif // !PLATE_H_
