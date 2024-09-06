#pragma once
#ifndef BREAK_H_
#include "Object.h"

class Break : public Object
{
public:
	enum class BreakType
	{
		NOTING, RED, BLUE, GREEN, YELLO, BLACK
	};
private:
	int brokenCount;
	BreakType type;
public:
	Break(POINT newPos, int _brokenCount) : Object()
	{
		width = 100;
		height = 50;
		pos = newPos;
		objTag = ObjectTag::BREAK;
		SetBreakType(_brokenCount);
		SetVertex();
	}

	void Draw(HDC& hdc, HBRUSH& hBrush, HBRUSH& oldBrush) override;
	void Update() override;
	bool OnCollision(Object& obj) override;
	void SetBreakType(int brokenCount);
	int GetbrokenCount() const { return brokenCount; }
};

#endif // !BREAK_H_
