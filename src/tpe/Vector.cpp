#include <tpe/Vector.h>

namespace tpe
{

glm::vec2 perp(glm::vec2 vec)
{
	return glm::vec2(-vec.y, vec.x);
}

}
