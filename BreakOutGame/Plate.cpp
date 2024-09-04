#include "Plate.h"

void Plate::Draw(HDC& hdc)
{
	POINT vertex[4] = { {pos.x - width / 2, pos.y - height / 2 },
						{pos.x + width / 2, pos.y - height / 2 },
						{pos.x + width / 2, pos.y + height / 2 },
						{pos.x - width / 2, pos.y + height / 2} };

	Polygon(hdc, vertex, 4);
}


void Plate::Move(int way)
{
	pos.x += way * movingSpeed;
	if (way > 0)
	{
		if (angle > 30) angle -= 5;
		nomalVec = { std::cos(angle * PI / 180), std::sin(angle * PI / 180) * -1 };
	}
	else
	{
		if (angle < 150) angle += 5;

		nomalVec = {std::cos(angle * PI / 180), std::sin(angle * PI / 180) * -1 };
	}

	if (world.right < pos.x + width/2 )
	{
		pos.x -= way * movingSpeed;
	}
	else if (world.left > pos.x - width /2)
	{
		pos.x += -1 * way * movingSpeed;
	}
}

void Plate::ChangeState(int itemState)
{
	switch (itemState)
	{
	case sNOTHING:
		width = 200;
		height = 20;
		movingSpeed = 20;
		break;
	case sLONG:
		width *= 2;
		break;
	case sSMALL:
		width /= 2;
		break;
	case sTRIPLE:
		break;
	default:

		break;
	}
}



void Plate::Update()
{

}

