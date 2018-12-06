
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
	float area; // asteroid area
    mat4 transform;
	std::vector<vec3> verts; // polygon vertices
	std::vector<vec3> Tverts; // transformed vertices

	enum AsteroidType {
		POLYROID,
		TRIROID,
		BARYROID
	};
	enum DrawStyle {
		OUTLINE,
		FILLED,
		TRIANGLES
	};

	AsteroidType type;
	DrawStyle drawstyle;

	Asteroid(vec3 position, float radius);
	Asteroid(vec3 position, std::vector<vec3> vertices);
	void transformVerts();
	void clip(std::vector<vec3> clipper);
	void setDrawStyle(DrawStyle ds);
	void update();
	void render(int);
};

#endif // ASTEROID_H

