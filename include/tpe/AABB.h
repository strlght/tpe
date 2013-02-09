#include <glm/glm.hpp>

namespace tpe
{

class AABB
{
public:
	float x1;
	float x2;
	float y1;
	float y2;

	AABB();
	AABB(float x1, float y1, float x2, float y2);
	bool collides(AABB aabb);
};

}
