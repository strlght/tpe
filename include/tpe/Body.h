#ifndef BODY_H
#define BODY_H

#include <vector>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <tpe/Polygon.h>

namespace tpe
{

class Polygon;

class Body
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	float angle;
	float angular_velocity;
	float m;
	float e;
	float u;
	bool isStatic;
	float i;

	std::vector<Polygon> shapes;

	Body();
	void applyImpulse(glm::vec2 impulse, glm::vec2 position);
	bool collides(Body *body);
	void updateRotation();
};

}

#endif
