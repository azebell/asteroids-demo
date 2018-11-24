#ifndef MISSILE_H
#define MISSILE_H

#include "zgeom.h"
#include <vector>

using namespace std;

class missile {
private:
public:
	vec3 pos;
	vec3 vel; // velocity
	float theta; // rotation
	mat4 transform;
	std::vector<vec3> verts; // line segment vertices
	std::vector<vec3> Tverts; // transformed vertices

	missile(float ShipTheta);
	void transformVerts();
	void clip(std::vector<vec3> clipper);
	void update();
	void render();
};

#endif 
