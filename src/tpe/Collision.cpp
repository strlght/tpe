#include <tpe/Collision.h>

void Collision::solve(Body *b1, Body *b2)
{
	float m1, m2, i1, i2; // mass and inertion of both bodies
	
	if (b1->isStatic)
	{
		m1 = INFINITY;
		i1 = INFINITY;
	}
	else
	{
		m1 = b1->mass;
		i1 = b1->inertion;
	}

	if (b2->isStatic)
	{
		m2 = INFINITY;
		i2 = INFINITY;
	}
	else
	{
		m2 = b2->mass;
		i2 = b2->inertion;
	}

	float friction = b1->friction * b2->friction;
	float bounce = b1->bounce * b2->bounce;

	glm::vec2 vel1 = b1->velocity + b1->angular_velocity * glm::vec2(-b1->velocity.y, b1->velocity.x); // todo: perp
	glm::vec2 vel2 = b2->velocity + b2->angular_velocity * glm::vec2(-b2->velocity.y, b2->velocity.x); // todo: perp

	glm::vec2 vr = vel2 - vel1;
	float vrn = glm::dot(vr, n);

	float totalbounce = vrn * bounce;
	float mass = 1.f / m1 + 1.f / m2;
	float r1n = r1.x * n.y - r1.y * n.x; // todo: perpdot
	float r2n = r2.x * n.y - r2.y * n.x; // todo: perpdot

	float kn = mass + pow(r1n, 2) / i1 + pow(r2n, 2) / i2;
	float nMass = 1.f / kn;

	float jn = max(- (totalbounce + vrn) * nMass, 0);
	glm::vec2 t = glm::vec2(-n.y, n.x);

	float vrt = vr.x * t.x + vr.y * t.y;

	float r1t = r1.x * t.y - r1.y * t.x;
	float r2t = r2.x * t.y - r2.y * t.x;

	float kt = mass + pow(r1t, 2) + pow(r2t, 2);
	float tMass = 1.f / kt;

	// friction
	float jtMax = bounce * jn;
	float jt = min(max(- vrt * tMass, -jtMax), jtMax);

	glm::vec2 j = n * jn + t * jt;

	b1->applyImpulse(-j, r1);
	b2->applyImpulse(j, r2);
}
