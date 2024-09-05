#include "Break.h"

void Break::Draw(HDC& hdc)
{

	switch (type)
	{
	case BreakType::RED:

		break;
	case BreakType::BLUE:
		break;
	case BreakType::GREEN:
		break;
	case BreakType::YELLO:
		break;
	case BreakType::BLACK:
		break;
	case BreakType::NOTING:
		return;
	}
	
	POINT vertex[4] = { {pos.x - width / 2, pos.y - height / 2 },
						{pos.x + width / 2, pos.y - height / 2 },
						{pos.x + width / 2, pos.y + height / 2 },
						{pos.x - width / 2, pos.y + height / 2} };

	Polygon(hdc, vertex, 4);
}

void Break::Update()
{

}

bool Break::OnCollision(Object& obj)
{
	--brokenCount;
	SetBreakType();

	return TRUE;
}

void Break::SetBreakType()
{
	switch (brokenCount)
	{
	case 1:
		BreakType::RED;
		break;
	case 2:
		BreakType::BLUE;
		break;
	case 3:
		BreakType::GREEN;
		break;
	case 4:
		BreakType::YELLO;
		break;
	case 5:
		BreakType::BLACK;
		break;
	default:
		BreakType::NOTING;
		ObjectTag::OBJ;
		break;
	}
}
