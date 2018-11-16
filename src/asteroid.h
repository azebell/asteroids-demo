#ifndef ASTEROID_H
#define ASTEROID_H

/*
#include "zgeom.h"	//***moved to includes
#include <vector>
*/

#include "includes.h"
#include "structs.h"

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

	Asteroid(vector3D position);
	void update();
	void render();
};

#endif // ASTEROID_H

