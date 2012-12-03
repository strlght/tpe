#include <tpe/Body.h>

void Body::applyImpulse(glm::vec2 impulse, glm::vec2 position)
{
	if (this->isStatic)
		return;
	this->velocity += impulse / this->mass;
	this->angular_velocity += (position.x * impulse.y - position.y * impulse.x) / this->inertion;
}

bool Body::collides(Body *body)
{
	for (Polygon p1 : this->shapes)
		for (Polygon p2 : body->shapes)
			if (p1.collides(&p2))
				return true;
	return false;
}

void Body::updateRotation()
{
	for (Polygon poly : this->shapes)
	{
		poly.updateRotation();
		poly.updateAABB();
	}
}
