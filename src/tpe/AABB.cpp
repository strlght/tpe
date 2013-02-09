#include <tpe/AABB.h>

namespace tpe
{

AABB::AABB()
{

}

AABB::AABB(float x1, float y1, float x2, float y2)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}

bool AABB::collides(AABB aabb)
{
	return (!((this->x1 > aabb.x2) || (this->x2 < aabb.x1) || (this->y1 < aabb.y2) || (this->y2 > aabb.y1)));
}

}
