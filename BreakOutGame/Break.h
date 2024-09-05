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
	Break(POINT newPos, int _brokenCount) : Object(), brokenCount(_brokenCount)
	{
		width = 100;
		height = 50;
		pos = newPos;
		objTag = ObjectTag::BREAK;
		SetBreakType();
	}
	// Object을(를) 통해 상속됨
	void Draw(HDC& hdc) override;
	void Update() override;
	bool OnCollision(Object& obj) override;
	void SetBreakType();
	int GetbrokenCount() const { return brokenCount; }
};

#endif // !BREAK_H_
