#pragma once
#ifndef OBJECT_H_
#include <Windows.h>

struct MyVector
{
	double x;
	double y;
};

class Object
{
protected:
	enum ObjectTag
	{
		OBJ,WALL, PLATE, BREAK, BALL
	};
	MyVector nomalVec;
	double height;
	double width;
	ObjectTag objTag;
	RECT world;
public:
	POINT pos;//ÁßÁ¡
	Object() { nomalVec = { 0,0 }; pos = { 0, 0 }; height = 0; width = 0; objTag = OBJ; world = { 0,0,0,0 }; }
	virtual void Draw(HDC& hdc) = 0;
	virtual void Update() = 0;
	virtual bool OnCollision(Object& obj);
	POINT GetCenter() const { return pos; }
	double GetHeight()const { return height; }
	double GetWidth() const { return width; }
	MyVector GetNomal() const { return nomalVec; }
	ObjectTag GetTag() const { return objTag; }
	void SetWorldView(RECT rec) { world = rec; }
};
#endif // !OBJECT_H_
