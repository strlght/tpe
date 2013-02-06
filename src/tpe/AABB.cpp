#include <tpe/AABB.h>

namespace tpe
{

AABB::AABB()
{

}

bool AABB::collides(AABB aabb)
{
	return (!((this->x1 > aabb.x2) || (this->x2 < aabb.x1) || (this->y1 < aabb.y2) || (this->y2 > aabb.y1)));
}

}
