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
		realPos.y = plate.pos.y - plate.GetHeight() / 2 - radius;
		realPos.x = plate.pos.x;
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
	//stay ���� �϶��� plate�� ��ǥ�� ���󰡾ߵ�
	//bounce ���� �϶��� ������ �ִ� moveVec�� ���� �����ߵȴ�.
}

bool Ball::OnCollision(Object& obj)
{
	switch (obj.GetTag())
	{
	case PLATE:
		{

			if ((realPos.y + radius) < (obj.pos.y - obj.GetHeight() / 2)) return false;

			if (realPos.x + radius <= obj.pos.x - obj.GetWidth() / 2
				|| realPos.x - radius >= obj.pos.x + obj.GetWidth() / 2)
			{
				realPos.y = realPos.y - radius - obj.GetHeight()/2;
				Reflection(obj);
				return true;
			}


			//if (realPos.x <= obj.GetCenter().x) // object�� �����ʿ��ִ�. ball�� ��������� ����
			//{
			//	if (realPos.x + radius <= obj.GetCenter().x - objHafWidth)
			//	{
			//		//�浹ó��
			//		Reflection(obj.GetNomal());
			//		return true;
			//	}
			//}
			//else
			//{
			//	if (realPos.x - radius >= obj.GetCenter().x + objHafWidth)
			//	{
			//		//�浹ó��
			//		Reflection(obj.GetNomal());
			//		return true;
			//	}
			//}
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
	dirVec = {0, -1};
}


void Ball::SetBallState(int newState)
{
	state = (BallState)newState;
}


