#include <tpe/Body.h>

namespace tpe
{

Body::Body(glm::vec2 position, float m, float u, float e, bool isStatic) :
	position(position), velocity(0, 0), angle(0), angular_velocity(0), m(m),
	i(0), e(e), u(u), isStatic(isStatic)
{
}

void Body::applyImpulse(glm::vec2 impulse, glm::vec2 position)
{
	if (this->isStatic)
		return;
	this->velocity += (impulse / this->m);
	this->angular_velocity += (perpdot(position, impulse) / this->i);
}

bool Body::collides(Body *body)
{
	for (Polygon &p1 : this->shapes)
		for (Polygon &p2 : body->shapes)
		{
			if (p1.aabb.collides(p2.aabb))
			{
				if (p1.collides(&p2))
				{
					return true;
				}
			}
		}
	return false;
}

void Body::updateRotation()
{
	for (Polygon &poly : this->shapes)
	{
		poly.updateRotation();
		poly.updateAABB();
	}
}

}
