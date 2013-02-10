#include <tpe/Solver.h>

namespace tpe
{

Solver::Solver(glm::vec2 position, glm::vec2 n, float depth, glm::vec2 r1, glm::vec2 r2)
{
	this->position = position;
	this->n = n;
	this->depth = depth;
	this->r1 = r1;
	this->r2 = r2;
}

void Solver::solve(Body *b1, Body *b2)
{
	float m1, m2, i1, i2; // mass and inertion of both bodies
	
	if (b1->isStatic)
	{
		m1 = INFINITY;
		i1 = INFINITY;
	}
	else
	{
		m1 = b1->m;
		i1 = b1->i;
	}

	if (b2->isStatic)
	{
		m2 = INFINITY;
		i2 = INFINITY;
	}
	else
	{
		m2 = b2->m;
		i2 = b2->i;
	}

	float e = b1->e * b2->e;
	float u = b1->u * b2->u;

	glm::vec2 vel1 = b1->velocity + b1->angular_velocity * perp(r1);
	glm::vec2 vel2 = b2->velocity + b2->angular_velocity * perp(r2);

	glm::vec2 vr = vel2 - vel1;
	float vrn = glm::dot(vr, n);

	float bounce = glm::dot(n, vr) * e;
	float mass = 1.f / m1 + 1.f / m2;
	float r1n = perpdot(r1, n);
	float r2n = perpdot(r2, n);

	float kn = mass + pow(r1n, 2) / i1 + pow(r2n, 2) / i2;
	float nMass = 1.f / kn;
	
	float jn = - (bounce + vrn) * nMass;

	glm::vec2 t = perp(n);

	float vrt = glm::dot(vr, t);

	float r1t = perpdot(r1, t);
	float r2t = perpdot(r1, t);

	float kt = mass + pow(r1t, 2) / i1 + pow(r2t, 2) / i2;
	float tMass = 1.f / kt;

	// friction
	float jtMax = u * jn;
	float jt = -vrt * tMass;
	jt = minval(maxval(jt, -jtMax), jtMax);

	glm::vec2 j = (n * jn + t * jt);

	b1->applyImpulse(-j, r1);
	b2->applyImpulse(j, r2);
}

}
