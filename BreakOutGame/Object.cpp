#include "Object.h"

bool Object::OnCollision(Object& obj)
{
	return false;
}

void Object::SetVertex()
{
	vertex[0] = { pos.x - (long)width / 2, pos.y - (long)height / 2 };
	vertex[1] = { pos.x + (long)width / 2, pos.y - (long)height / 2 };
	vertex[2] = { pos.x + (long)width / 2, pos.y + (long)height / 2 };
	vertex[3] = { pos.x - (long)width / 2, pos.y + (long)height / 2 };
}
