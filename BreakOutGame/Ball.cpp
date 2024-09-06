#include "Ball.h"
#include "Break.h"

void Ball::Draw(HDC& hdc, HBRUSH & hBrush, HBRUSH & oldBrush)
{
	pos.x = realPos.x;
	pos.y = realPos.y;
	Ellipse(hdc, pos.x - 10, pos.y - 10, pos.x + 10, pos.y + 10);
}

void Ball::Update()
{
	
}

void Ball::Update(Object& plate)
{
	switch (state)
	{
	case BallState::STAY:
		if (!isAlive) initState(plate);
		realPos.y = plate.GetCenter().y - plate.GetHeight() / 2 - radius;
		realPos.x = plate.GetCenter().x;
		pos.x = realPos.x;
		pos.y = realPos.y;
		break;
	case BallState::BOUNCE:
		realPos.x += dirVec.x * speed;
		realPos.y += dirVec.y * speed;
		break;
	}

	if (realPos.y >= world.bottom + 100)
	{
		isAlive = false;
		state = BallState::STAY;
	}
	//stay 상태 일때는 plate의 좌표를 따라가야됨
	//bounce 상태 일때는 가지고 있는 moveVec을 따라서 날려야된다.
}

bool Ball::OnCollision(Object& obj)
{
	bool isCollision = false;
	switch (obj.GetTag())
	{
	case ObjectTag::WALL:
		{
			if (realPos.x + radius > obj.GetCenter().x + obj.GetWidth()/2)			dirVec.x *= -1;
			else if (realPos.x - radius < obj.GetCenter().x - obj.GetWidth()/2)					dirVec.x *= -1;
			else if (realPos.y + radius > obj.GetHeight() )
			{
		
			}
			else if (realPos.y - radius < 0)					dirVec.y *= -1;
		}
		break;
	case ObjectTag::PLATE:
		{
			/*if (!(realPos.y + radius <= obj.GetCenter().y + obj.GetHeight() / 2 &&
				realPos.y - radius <= obj.GetCenter().y + obj.GetHeight() / 2 &&
				realPos.y + radius >= obj.GetCenter().y - obj.GetHeight() / 2 &&
				realPos.y - radius >= obj.GetCenter().y - obj.GetHeight() / 2)) return false;*/

			if (realPos.y + radius <= obj.GetCenter().y - obj.GetHeight() / 2) return false;

			if((realPos.x + radius <= obj.GetCenter().x + obj.GetWidth() / 2 ||
				realPos.x - radius <= obj.GetCenter().x + obj.GetWidth() / 2) &&
				(realPos.x + radius >= obj.GetCenter().x - obj.GetWidth() / 2 ||
				realPos.x - radius >= obj.GetCenter().x - obj.GetWidth() / 2))
			{
				//충돌처리
				Reflection(obj);
				return true;
			}
			
			return false;
		}
		
	case ObjectTag::BREAK:
		{
			//if (!(realPos.y + radius >= obj.GetCenter().y - obj.GetHeight() / 2 &&
			//	realPos.y + radius <= obj.GetCenter().y + obj.GetHeight() / 2 &&
			//	realPos.y - radius <= obj.GetCenter().y + obj.GetHeight() / 2 &&
			//	realPos.y - radius >= obj.GetCenter().y - obj.GetHeight() / 2)) return false;

			//if ((realPos.x + radius <= obj.GetCenter().x + obj.GetWidth() / 2 ||
			//	realPos.x - radius <= obj.GetCenter().x + obj.GetWidth() / 2) &&
			//	(realPos.x + radius >= obj.GetCenter().x - obj.GetWidth() / 2 ||
			//	realPos.x - radius >= obj.GetCenter().x - obj.GetWidth() / 2))
			//{
			//	//충돌처리
			//	Reflection(obj);
			//	return true;
			//}

			if (obj.GetVertex()[0].x <= realPos.x && obj.GetVertex()[1].x >= realPos.x)
			{
				if (obj.GetVertex()[0].y - radius >= realPos.y && obj.GetVertex()[0].y <= realPos.y) isCollision = true;
				if (obj.GetVertex()[3].y + radius <= realPos.y && obj.GetVertex()[3].y >= realPos.y) isCollision = true;
			}
			else if (obj.GetVertex()[0].x - radius <= realPos.x && obj.GetVertex()[0].x >= realPos.x)
			{
				if (obj.GetVertex()[0].y - radius >= realPos.y && obj.GetVertex()[0].y <= realPos.y) isCollision = true;
				if (obj.GetVertex()[3].y + radius <= realPos.y && obj.GetVertex()[3].y >= realPos.y) isCollision = true;
			}
			else if (obj.GetVertex()[1].x + radius >= realPos.x && obj.GetVertex()[1].x <= realPos.x)
			{
				if (obj.GetVertex()[0].y - radius >= realPos.y && obj.GetVertex()[0].y <= realPos.y) isCollision = true;
				if (obj.GetVertex()[3].y + radius <= realPos.y && obj.GetVertex()[3].y >= realPos.y) isCollision = true;
			}
			//모서리 처리(각 점 위치에서 radius거리 안에 있으면 충돌~
			else
			{

			}
		}
			break;
	}
}

void Ball::initState(Object& plate)
{
	dirVec = { 0,-1 };
	angle = 90;
	isAlive = true;
}



void Ball::Reflection(Object& obj)
{
	//realPos.y = obj.GetCenter().y - obj.GetHeight() / 2 - radius;

	if (obj.GetTag() == ObjectTag::PLATE)	dirVec = obj.GetNomal();
	else if(obj.GetTag() == ObjectTag::BREAK)
	{
		if (realPos.x + radius > obj.GetCenter().x + obj.GetWidth() / 2)			dirVec.x *= -1;
		else if (realPos.x - radius < obj.GetCenter().x - obj.GetWidth() / 2)		dirVec.x *= -1;
		else if (realPos.y + radius > obj.GetHeight())								dirVec.y *= -1;
		else if (realPos.y - radius < 0)											dirVec.y *= -1;
		obj.OnCollision(obj);
	}

}


void Ball::SetBallState(BallState newState)
{
	state = newState;
}


