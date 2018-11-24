
#ifndef MISSILE_H
#define MISSILE_H

#include "zgeom.h"
#include <vector>

class Missile {
private:
public:
	vec3 pos; // position
	vec3 vel; // velocity
	float theta; // rotation
	mat4 transform;
	std::vector<vec3> verts; // line segment vertices
	std::vector<vec3> Tverts; // transformed vertices

	Missile(vec3 position, float angle);
	void transformVerts();
	void update();
	void render();
};

#endif  // MISSILE_H

