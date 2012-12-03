#ifndef BODY_H
#define BODY_H

#include <vector>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <tpe/Polygon.h>

class Polygon;

class Body
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	float angle;
	float angular_velocity;
	float mass;
	float friction;
	float bounce;
	bool isStatic;
	float inertion;

	std::vector<Polygon> shapes;

	void applyImpulse(glm::vec2 impulse, glm::vec2 position);
	bool collides(Body *body);
	void updateRotation();
};

#endif
