#include <vector>
#include <glm/glm.hpp>
#include <tpe/Body.h>

class World
{
public:
	float depth;

	glm::vec2 gravity;
	std::vector<Body*> bodies;

	void step(float t, int iterations);
};
