#include <cmath>
#include "Ball.h"
#include "Break.h"
#define VERTEXNUM 4

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
	//stay ���� �϶��� plate�� ��ǥ�� ���󰡾ߵ�
	//bounce ���� �϶��� ������ �ִ� moveVec�� ���� �����ߵȴ�.
}

bool Ball::OnCollision(Object& obj)
{
	bool isCollision = false;
	switch (obj.GetTag())
	{
	case ObjectTag::WALL:
		{
			if (realPos.x + radius > obj.GetCenter().x + obj.GetWidth()/2)			dirVec.x *= -1;
			else if (realPos.x - radius < obj.GetCenter().x - obj.GetWidth()/2)		dirVec.x *= -1;
			else if (realPos.y + radius > obj.GetHeight() )
			{
		
			}
			else if (realPos.y - radius < 0)					dirVec.y *= -1;
		}
		break;
	case ObjectTag::PLATE:
		{
			//�����¿� �浹ó�� -> �ؾߵ� �� : ���⺤�Ͱ� 1 1 �� �Ǽ� ������ ���� ����ȭ ������ �ʿ�
			if (obj.GetVertex()[0].x <= realPos.x && obj.GetVertex()[1].x >= realPos.x)
			{
				if (obj.GetVertex()[0].y - radius <= realPos.y && obj.GetVertex()[0].y >= realPos.y) { isCollision = true; }
				if (obj.GetVertex()[3].y + radius >= realPos.y && obj.GetVertex()[3].y <= realPos.y) { isCollision = true; }
				if (isCollision) { dirVec = obj.GetNomal(); }
			}
			else if (obj.GetVertex()[0].y <= realPos.y && obj.GetVertex()[3].y >= realPos.y)
			{
				if (obj.GetVertex()[0].x - radius <= realPos.x && obj.GetVertex()[0].x >= realPos.x) { isCollision = true; }
				if (obj.GetVertex()[1].x + radius >= realPos.x && obj.GetVertex()[1].x <= realPos.x) { isCollision = true; }
				if (isCollision){ dirVec.x *= -1; }
			}
			//�𼭸� ó�� �� ��(4��) ��ġ���� radius�Ÿ� �ȿ� ������ �浹~
			else
			{
				double len;
				for (int i = 0; i < VERTEXNUM; i++)
				{
					len = sqrt(pow((obj.GetVertex()[i].x - realPos.x), 2) + pow((obj.GetVertex()[i].y - realPos.y), 2));
					if (radius >= len) { isCollision = true; }
					if (isCollision && !isOverlapCollision)
					{
						isOverlapCollision = true;
						dirVec.x *= -1; dirVec.y *= -1;
						break;
					}
				}
			}

			//
			//if (realPos.y + radius <= obj.GetCenter().y - obj.GetHeight() / 2) return isCollision;

			//if((realPos.x + radius <= obj.GetCenter().x + obj.GetWidth() / 2 ||
			//	realPos.x - radius <= obj.GetCenter().x + obj.GetWidth() / 2) &&
			//	(realPos.x + radius >= obj.GetCenter().x - obj.GetWidth() / 2 ||
			//	realPos.x - radius >= obj.GetCenter().x - obj.GetWidth() / 2))
			//{
			//	//�浹ó��
			//	isCollision = true;
			//	dirVec = obj.GetNomal();
			//}
		}
		break;
	case ObjectTag::BREAK:
		{
			//�����¿� �浹ó�� -> �ؾߵ� �� : ���⺤�Ͱ� 1 1 �� �Ǽ� ������ ���� ����ȭ ������ �ʿ�
			if (obj.GetVertex()[0].x <= realPos.x && obj.GetVertex()[1].x >= realPos.x)
			{
				if (obj.GetVertex()[0].y - radius <= realPos.y && obj.GetVertex()[0].y >= realPos.y) { isCollision = true; }
				if (obj.GetVertex()[3].y + radius >= realPos.y && obj.GetVertex()[3].y <= realPos.y) { isCollision = true; }
				if (isCollision && !isOverlapCollision)
				{
					isOverlapCollision = true;
					dirVec.y *= -1;
				}
			}
			else if (obj.GetVertex()[0].y <= realPos.y && obj.GetVertex()[3].y >= realPos.y)
			{
				if (obj.GetVertex()[0].x - radius <= realPos.x && obj.GetVertex()[0].x >= realPos.x) { isCollision = true; }
				if (obj.GetVertex()[1].x + radius >= realPos.x && obj.GetVertex()[1].x <= realPos.x) { isCollision = true; }
				if (isCollision && !isOverlapCollision)
				{
					isOverlapCollision = true;
					dirVec.x *= -1;
				}
			}
			//�𼭸� ó�� �� ��(4��) ��ġ���� radius�Ÿ� �ȿ� ������ �浹~
			else
			{
				double len;
				for (int i = 0; i < VERTEXNUM; i++)	
				{
					len = sqrt(pow((obj.GetVertex()[i].x - realPos.x), 2) + pow((obj.GetVertex()[i].y - realPos.y), 2));
					if (radius >= len) { isCollision = true; }
					if (isCollision && !isOverlapCollision) 
					{
						isOverlapCollision = true;
						dirVec.x *= -1; dirVec.y *= -1; 
						break; 
					}
				}
			}
		}
			break;
	}

	if (isCollision) obj.OnCollision(obj);
	return isCollision;
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

	obj.OnCollision(obj);
}


void Ball::SetBallState(BallState newState)
{
	state = newState;
}


