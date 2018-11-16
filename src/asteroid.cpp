/*
#include <math.h> // for trig		//***moved to includes
#include <cstdlib> // for rand()
*/

#include "includes.h"
#include "structs.h"
#include "asteroid.h"

float rand_range(float range) {
	float r = ((rand()%100)/50.0) - 1.0;
	return r*range;
}

Asteroid::Asteroid(vector3D position) :
pos(position) {
	float PI = 3.14159265359;
	this->vel = {rand_range(10),rand_range(10),0.0};
	this->theta = 0.0;
	this->alpha = rand_range(1.0);

	float iwx = 1 - rand_range(0.5), wx = iwx;
	float iwy = 1 - rand_range(0.5), wy = iwy;
	float r = 50; // radius of asteroid
	int p = 8; // number of points in asteroid
	for(int i=0; i<p; i++) {
		this->verts.push_back( vector3D(wx*r* (float)cos(i*2*PI/p), wy*r* (float)sin(i*2*PI/p), 0));

		wx = 1 - rand_range(0.5);
		wy = 1 - rand_range(0.5);
	}
	this->Tverts = verts;
}

void Asteroid::update() {
	this->pos.x += this->vel.x;
	this->pos.y += this->vel.y;
	this->pos.z += this->vel.z;
	this->theta += this->alpha;

}

void Asteroid::render() {

}

