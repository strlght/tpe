#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <glm/glm.hpp>
#include <tpe/Body.h>
#include <tpe/Vector.h>

#ifndef maxval
#define maxval(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef minval
#define minval(a,b)            (((a) < (b)) ? (a) : (b))
#endif

namespace tpe
{

class Body;

class Collision
{
public:
	glm::vec2 position;
	glm::vec2 n;
	glm::vec2 r1;
	glm::vec2 r2;
	float depth;

	Collision();
	void solve(Body *b1, Body *b2);
};

}

#endif
