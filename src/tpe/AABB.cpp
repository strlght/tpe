#include <tpe/AABB.h>

bool AABB::collides(AABB *aabb)
{
	if (this->x2 < aabb->x1 ||
			this->x1 > aabb->x2 ||
			this->y1 > aabb->y2 ||
			this->y2 < aabb->y1)
		return false;
	return true;
}
