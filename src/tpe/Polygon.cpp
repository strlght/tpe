#include <tpe/Polygon.h>

namespace tpe
{

Polygon::Polygon(Body *body, std::vector<glm::vec2> vertices)
{
	this->body = body;

	for (glm::vec2 vert : vertices)
	{
		this->vertices.push_back(vert);
		this->base_vertices.push_back(vert);
	}

	for (int i = 0; i < this->vertices.size(); i++)
	{
		Edge edge;
		glm::vec2 first = this->vertices[i], second = this->vertices[(i + 1) % this->vertices.size()];
		glm::vec2 result = second - first;
		edge.n = glm::normalize(perp(result));
		edge.d = glm::dot(edge.n, first);
		this->edges.push_back(edge);
		this->base_edges.push_back(edge);
	}
	
	this->body->shapes.push_back(*this);

	this->updateRotation();
	this->updateAABB();
}

float Polygon::IMoment()
{
	float ti = 0, j = 0;

	for (int i = 0; i < this->vertices.size(); i++)
	{
		glm::vec2 first = this->base_vertices[i], second = this->base_vertices[(i + 1) % this->vertices.size()];

		float pd = perpdot(second, first);
		float sumdot = glm::dot(first, second) + glm::dot(first, first) + glm::dot(second, second);

		ti += pd * sumdot;
		j += pd + sumdot;
	}

	return (body->m * ti) / (6.f * j);
}

float Polygon::edgeDistance(glm::vec2 n, float d)
{
	float m = glm::dot(n, this->vertices[0]);

	for (int i = 1; i < this->vertices.size(); i++)
		if (glm::dot(n, this->vertices[i]) < m)
			m = glm::dot(n, this->vertices[i]);

	return m - d;
}

int Polygon::minEdgeDistanceTo(Polygon *polygon, float &dist)
{
	int index = 0;
	float min = this->edgeDistance(polygon->edges[0].n, polygon->edges[0].d), d;

	if (min > 0.f)
		return -1;

	for (int i = 1; i < polygon->edges.size(); i++)
	{
		d = this->edgeDistance(polygon->edges[i].n, polygon->edges[i].d);

		if (d > 0.f)
			return -1;
		else if (min < d)
		{
			min = d;
			index = i;
		}
	}
	dist = d;
	return index;
}

bool Polygon::containsPoint(glm::vec2 point)
{
	for (int i = 0; i < this->vertices.size(); i++)
		if (glm::dot(this->edges[i].n, point) - this->edges[i].d > 0.f)
			return false;
	return true;
}

void Polygon::checkIntersection(Polygon *polygon, glm::vec2 n, float d)
{
	float k;

	d = abs(d);

	for (int i = 0; i < this->vertices.size(); i++)
	{
		if (polygon->containsPoint(this->vertices[i]))
		{
			float depth = d * this->body->world->depth;
			Solver collision(this->vertices[i],
					n,
					depth,
					this->vertices[i] - this->body->position,
					this->vertices[i] - polygon->body->position);

			if (this->body->isStatic)
				k = 0.f;
			else if (polygon->body->isStatic)
				k = 1.f;
			else
				k = .5f;

			if (!this->body->isStatic)
				this->body->position -= n * (k * depth);
			if (!polygon->body->isStatic)
				polygon->body->position += n * ((1 - k) * depth);

			collision.solve(this->body, polygon->body);
		}
	}
}

bool Polygon::collides(Polygon *polygon)
{
	float min_dist1 = 0.f, min_dist2 = 0.f;

	int min_index1 = polygon->minEdgeDistanceTo(this, min_dist1);
	int min_index2 = this->minEdgeDistanceTo(polygon, min_dist2);

	if (min_index1 == -1)
		return false;

	if (min_index2 == -1)
		return false;

	if (min_dist1 > min_dist2)
		this->checkIntersection(polygon, this->edges[min_index1].n, min_dist1);
	else
		this->checkIntersection(polygon, -polygon->edges[min_index2].n, min_dist2);

	return true;
}

void Polygon::updateAABB()
{
	this->aabb.x1 = this->vertices[0].x;
	this->aabb.x2 = this->vertices[0].x;
	this->aabb.y1 = this->vertices[0].y;
	this->aabb.y2 = this->vertices[0].y;

	for (glm::vec2 vertex : this->vertices)
	{
		if (vertex.x < this->aabb.x1) this->aabb.x1 = vertex.x;
		if (vertex.x > this->aabb.x2) this->aabb.x2 = vertex.x;
		if (vertex.y > this->aabb.y1) this->aabb.y1 = vertex.y;
		if (vertex.y < this->aabb.y2) this->aabb.y2 = vertex.y;
	}
}

void Polygon::updateRotation()
{
	for (int i = 0; i < this->vertices.size(); i++)
	{
		glm::vec2 pos = glm::rotate(this->base_vertices[i], this->body->angle);
		this->vertices[i] = this->body->position + pos;
		this->edges[i].n = glm::rotate(this->base_edges[i].n, this->body->angle);
		this->edges[i].d = glm::dot(this->body->position, this->edges[i].n) + this->base_edges[i].d;
	}
}

}
