#include "Break.h"

void Break::Draw(HDC& hdc, HBRUSH & hBrush, HBRUSH & oldBrush)
{

	switch (type)
	{
	case BreakType::RED:
		hBrush = CreateSolidBrush(RGB(205, 92, 92));
		break;
	case BreakType::BLUE:
		hBrush = CreateSolidBrush(RGB(80, 133, 188));
		break;
	case BreakType::GREEN:
		hBrush = CreateSolidBrush(RGB(102, 205, 170));
		break;
	case BreakType::YELLO:
		hBrush = CreateSolidBrush(RGB(243, 229, 171));
		break;
	case BreakType::BLACK:
		hBrush = CreateSolidBrush(RGB(65, 65, 65));
		break;
	case BreakType::NOTING:
		return;
	}

	oldBrush = (HBRUSH)SelectObject(hdc,hBrush);
	

	Polygon(hdc, vertex, 4);
	DeleteObject(hBrush);
}

void Break::Update()
{

}

bool Break::OnCollision(Object& obj)
{
	--brokenCount;
	SetBreakType(brokenCount);

	return TRUE;
}

void Break::SetBreakType(int _brokenCount)
{
	brokenCount = _brokenCount;
	switch (brokenCount)
	{
	case 1:
		type = BreakType::RED;
		break;
	case 2:
		type = BreakType::BLUE;
		break;
	case 3:
		type = BreakType::GREEN;
		break;
	case 4:
		type = BreakType::YELLO;
		break;
	case 5:
		type = BreakType::BLACK;
		break;
	default:
		type = BreakType::NOTING;
		objTag = ObjectTag::OBJ;
		break;
	}
}
