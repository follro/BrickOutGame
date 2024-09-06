#include "Wall.h"

void Wall::Draw(HDC& hdc, HBRUSH & hBrush, HBRUSH & oldBrush)
{
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void Wall::Update()
{

}


