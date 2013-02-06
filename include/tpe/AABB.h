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
	bool collides(AABB aabb);
};

}
