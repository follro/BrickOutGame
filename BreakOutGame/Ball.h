#pragma once
#ifndef BALL_H_
#include "Object.h"
#include "Plate.h"
#include "Wall.h"

class Ball : public Object
{
public:
	enum class BallState
	{
		STAY, BOUNCE
	};
private:
	MyVector realPos;
	MyVector dirVec;
	double angle;
	double speed;
	double radius;
	BallState state;
	BOOL isAlive;
	BOOL isOverlapCollision;
public:
	Ball() : Object()
	{
		realPos = { 0,0 };
		dirVec = { 0,-1};
		angle = 0;
		speed = 10;
		radius = 10;
		state = BallState::STAY;
		objTag = ObjectTag::BALL;
		isAlive = true;
		isOverlapCollision = false;
	}
	void Draw(HDC& hdc, HBRUSH& hBrush, HBRUSH& oldBrush) override;
	void Update() override;
	void Update(Object& obj);
	bool OnCollision(Object& obj) override;
	void initState(Object& obj);
	void Reflection(Object& obj );
	void SetBallState(BallState newState);
	BallState GetBallState() const{ return state; }
	void ResetOverLapCollision() { isOverlapCollision = false; }
};

 
#endif