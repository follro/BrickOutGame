#include "Ball.h"

void Ball::Draw(HDC& hdc)
{
	pos.x = realPos.x;
	pos.y = realPos.y;
	Ellipse(hdc, pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10);
}

void Ball::Update()
{
	
}

void Ball::Update(Plate& plate)
{
	switch (state)
	{
	case STAY:
		if (!isAlive) initState(plate);
		realPos.y = plate.GetCenter().y - plate.GetHeight() / 2 - radius;
		realPos.x = plate.GetCenter().x;
		pos.x = realPos.x;
		pos.y = realPos.y;
		break;
	case BOUNCE:
		realPos.x += dirVec.x * speed;
		realPos.y += dirVec.y * speed;
		break;
	}

	if (realPos.y >= world.bottom + 100)
	{
		isAlive = false;
		state = STAY;
	}
	//stay 상태 일때는 plate의 좌표를 따라가야됨
	//bounce 상태 일때는 가지고 있는 moveVec을 따라서 날려야된다.
}

bool Ball::OnCollision(Object& obj)
{
	switch (obj.GetTag())
	{
	case PLATE:
		{

			if ((realPos.y + radius) < (obj.GetCenter().y - obj.GetHeight() / 2)) return false;

			if (realPos.x <= obj.GetCenter().x) // object가 오른쪽에있다. ball은 상대적으로 왼쪽
			{
				if (realPos.x + radius >= obj.GetCenter().x - obj.GetWidth() / 2 &&
					realPos.x + radius < obj.GetCenter().x + obj.GetWidth()/2 )
				{
					//충돌처리
					Reflection(obj);
					return true;
				}
			}
			else
			{
				if (realPos.x - radius <= obj.GetCenter().x + obj.GetWidth() / 2 &&
					realPos.x - radius > obj.GetCenter().x - obj.GetWidth() /2)
				{
					//충돌처리
					Reflection(obj);
					return true;
				}
			}
			return false;
		}
		break;
	case WALL:
		{
			if (realPos.x + radius > obj.GetWidth())			dirVec.x *= -1;
			else if (realPos.x - radius < 0)					dirVec.x *= -1;
			else if (realPos.y + radius > obj.GetHeight() )
			{
		
			}
			else if (realPos.y - radius < 0)					dirVec.y *= -1;
		}
		break;
	}
}

void Ball::initState(Plate& plate)
{
	dirVec = { 0,-1 };
	angle = 90;
	isAlive = true;
}



void Ball::Reflection(Object& obj)
{
	realPos.y = obj.GetCenter().y - obj.GetHeight() / 2 - radius;
	dirVec = obj.GetNomal();
}


void Ball::SetBallState(int newState)
{
	state = (BallState)newState;
}


