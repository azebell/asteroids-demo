
#include "asteroid.h"
#include <math.h>
#include <cstdlib>
#include "glFuncs.h"

float rand_range(float range) {
	float r = ((rand()%100)/50.0) - 1.0;
	return r*range;
}

// creating Asteroid with random geometry
Asteroid::Asteroid(vec3 position, float radius) :
pos(position) {
	float PI = 3.14159265359;
	this->vel = {rand_range(2.5),rand_range(2.5),0.0};
	this->theta = 0.0;
	this->alpha = rand_range(0.1);

	float iwx = 1 - rand_range(0.5), wx = iwx;
	float iwy = 1 - rand_range(0.5), wy = iwy;
	int p = 8; // number of points in asteroid
	for(int i=0; i<p; i++) {
		this->verts.push_back( {
			wx*radius* (float)cos(i*2*PI/p),
			wy*radius* (float)sin(i*2*PI/p)
		});

		wx = 1 - rand_range(0.5);
		wy = 1 - rand_range(0.5);
	}
	this->Tverts = verts;
}

// creating Asteroid with predefined geometry
Asteroid::Asteroid(vec3 position, std::vector<vec3> vertices) :
pos(position), verts(vertices) {
	this->vel = {rand_range(2.5),rand_range(2.5),0.0};
	this->theta = 0.0;
	this->alpha = rand_range(0.1);

	this->Tverts = verts;
}

void Asteroid::transformVerts() {
	this->transform = mat4Identity();
	mat4RotateZ(&this->transform, this->theta);
	mat4Translate(&this->transform, this->pos);
	this->Tverts = applyTransform(this->transform, this->verts);
}

void Asteroid::clip(std::vector<vec3> clipper) {
	this->Tverts = clip_sh(this->Tverts, clipper);
}

void Asteroid::update() {
	this->pos.x += this->vel.x;
	this->pos.y += this->vel.y;
	this->pos.z += this->vel.z;
	this->theta += this->alpha;

	this->transformVerts();
}

void Asteroid::render() {
	// draw the asteroid
	glBegin(GL_LINE_LOOP);
	for(unsigned i=0; i < this->Tverts.size(); i++) {
		glVertex3f(this->Tverts[i].x, this->Tverts[i].y, 0.0);
	}
	glEnd();
}

