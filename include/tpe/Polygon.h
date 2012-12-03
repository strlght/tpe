#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <cmath>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <tpe/AABB.h>
#include <tpe/Collision.h>
#include <tpe/Body.h>

struct Edge
{
	glm::vec2 n;
	float d;
};

class Body;

class Polygon
{
public:
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> base_vertices;

	std::vector<Edge> edges;
	std::vector<Edge> base_edges;
	glm::vec2 rotation;
	Body *body;
	AABB *aabb;

	Polygon(Body *body, std::vector<glm::vec2> vertices);
	float IMoment();
	float edgeDistance(glm::vec2 n, float d);
	int minEdgeDistanceTo(Polygon *polygon, float &dist);
	bool containsPoint(glm::vec2 point);
	void checkIntersection(Polygon *polygon, glm::vec2 n, float d);
	bool collides(Polygon *polygon);
	void updateAABB();
	void updateRotation();
};

#endif
