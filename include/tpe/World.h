#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/glm.hpp>
#include <tpe/Body.h>

namespace tpe
{

class Body;

class World
{
public:
	float depth;

	glm::vec2 gravity;
	std::vector<Body*> bodies;

	World(float depth);
	void addBody(Body* body);
	void step(float t, int iterations);
};

}

#endif
