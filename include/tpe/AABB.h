#include <glm/glm.hpp>
#include <vector>

class AABB
{
public:
	float x1;
	float x2;
	float y1;
	float y2;

	bool collides(AABB *aabb);
};
