#ifndef ASTEROID_H
#define ASTEROID_H

#include "zgeom.h"
#include <vector>

using namespace std;

class Asteroid {
private:
public:
	vector3D pos; // position
	vector3D vel; // velocity
	float theta; // rotation
	float alpha; // rotational velocity
	//mat4 transform;
	vector<vector3D> verts; // polygon vertices
	vector<vector3D> Tverts; // transformed vertices

	enum AsteroidType {
		POLYROID,
		TRIROID,
		BARYROID
	};

	AsteroidType type;

	Asteroid(vec3 position, float radius);
	Asteroid(vec3 position, std::vector<vec3> vertices);
	void transformVerts();
	void clip(std::vector<vec3> clipper);

	void update();
	void render();
};

#endif // ASTEROID_H

