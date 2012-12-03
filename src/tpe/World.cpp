#include <tpe/World.h>

void World::step(float t, int iterations)
{
	float dt = t / iterations;
	for (int iter = 0; iter < iterations; iter++)
	{
		for (Body *body : this->bodies)
		{
			if (!body->isStatic)
				body->velocity += gravity * dt;
			body->angle += body->angular_velocity * dt;
			body->position += body->velocity * dt;
		}

		for (int i = 0; i < this->bodies.size(); i++)
		{
			for (int j = 0; j < this->bodies.size(); j++)
			{
				if (i > j || this->bodies[i]->collides(this->bodies[j]))
					break;
			}
		}
	}
}
