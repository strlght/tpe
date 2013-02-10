#include <tpe/Vector.h>

namespace tpe
{

glm::vec2 perp(glm::vec2 vec)
{
	return glm::vec2(-vec.y, vec.x);
}

float perpdot(glm::vec2 a, glm::vec2 b)
{
	return - glm::dot(a, perp(b));
}

}
