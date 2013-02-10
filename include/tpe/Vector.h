#ifndef VECTOR_H
#define VECTOR_H

#define GLM_SWIZZLE
#include <glm/glm.hpp>

namespace tpe
{

glm::vec2 perp(glm::vec2 vec);
float perpdot(glm::vec2 a, glm::vec2 b);

}

#endif
