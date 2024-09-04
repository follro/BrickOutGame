#pragma once
#ifndef BALL_H_
#include "Object.h"
#include "Plate.h"
#include "Wall.h"

class Ball : public Object
{
	enum BallState
	{
		STAY, BOUNCE
	};
	MyVector realPos;
	MyVector dirVec;
	double angle;
	double speed;
	double radius;
	BallState state;
	BOOL isAlive;
public:
	Ball() : Object()
	{
		realPos = { 0,0 };
		dirVec = { 0,-1};
		angle = 0;
		speed = 10;
		radius = 10;
		state = STAY;
		objTag = BALL;
		isAlive = true;
	}
	void Draw(HDC& hdc) override;
	void Update() override;
	void Update(Plate& plate);
	bool OnCollision(Object& obj) override;
	void initState(Plate& plate);
	void Reflection(Object& obj );
	void SetBallState(int newState);
	int GetBallState() const{ return state; }
	void SetPlate(Plate plate) {
		realPos.y = plate.pos.y - plate.GetHeight() / 2 - radius;
		realPos.x = plate.pos.x;
	}
};


#endif