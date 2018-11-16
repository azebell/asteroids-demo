
#ifndef ASTEROID_H
#define ASTEROID_H

#include "zgeom.h"
#include <vector>

class Asteroid {
private:
public:
	vec3 pos; // position
	vec3 vel; // velocity
	float theta; // rotation
	float alpha; // rotational velocity
	mat4 transform;
	std::vector<vec3> verts; // polygon vertices
	std::vector<vec3> Tverts; // transformed vertices

	Asteroid(vec3 position);
	Asteroid(vec3 position, std::vector<vec3> vertices);
	void update();
	void render();
};

#endif // ASTEROID_H

