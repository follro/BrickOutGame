#include "Wall.h"

void Wall::Draw(HDC& hdc)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void Wall::Update()
{

}


