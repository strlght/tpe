#include <vector>
#include <glm/glm.hpp>
#include <tpe/Body.h>

namespace tpe
{

class World
{
public:
	float depth;

	glm::vec2 gravity;
	std::vector<Body*> bodies;

	World();
	void step(float t, int iterations);
};

}
