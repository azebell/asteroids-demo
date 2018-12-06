
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
	this->vel = {rand_range(1.0),rand_range(1.0),0.0};
	this->theta = 0.0;
	this->alpha = rand_range(0.05);

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
	this->transformVerts();
	this->type = Asteroid::POLYROID;
	this->drawstyle = OUTLINE;
    std::vector<vec3> tris = triangulate(verts, CCW_WINDING);
    this->area = area_of_tris(tris);
	this->clipped = 0;
}

// creating Asteroid with predefined geometry
Asteroid::Asteroid(vec3 position, std::vector<vec3> vertices) :
pos(position), verts(vertices) {
	this->vel = {rand_range(1.0),rand_range(1.0),0.0};
	this->theta = 0.0;
	this->alpha = rand_range(0.05);

	this->transformVerts();
	this->type = Asteroid::POLYROID;
	this->drawstyle = OUTLINE;
    std::vector<vec3> tris = triangulate(verts, CCW_WINDING);
    this->area = area_of_tris(tris);
	this->clipped = 0;
}

void Asteroid::transformVerts() {
	this->transform = mat4Identity();
	mat4RotateZ(&this->transform, this->theta);
	mat4Translate(&this->transform, this->pos);
	this->Tverts = applyTransform(this->transform, this->verts);
}

void Asteroid::clip(std::vector<vec3> clipper) {
	this->Tverts = clip_sh(this->Tverts, clipper);
	this->clipped = 1;
}

void Asteroid::setDrawStyle(DrawStyle ds) {
	this->drawstyle = ds;
}

void Asteroid::update() {
	this->pos.x += this->vel.x;
	this->pos.y += this->vel.y;
	this->pos.z += this->vel.z;
	this->theta += this->alpha;

	this->transformVerts();
	this->drawstyle = OUTLINE;

	this->clipped = 0;
}

void Asteroid::render(int tessControl) {
	glColor3ub(255,255,255);
	
	std::vector<vec3> tris;
	if(this->drawstyle == FILLED || tessControl == 1)
	tris = triangulate(this->Tverts, CCW_WINDING);
	switch(this->drawstyle) {
		case OUTLINE:
			// draw the asteroid
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			if(tessControl == 0){
				glBegin(GL_LINE_LOOP);
				for(unsigned i=0; i < this->Tverts.size(); i++) {
					glVertex3f(this->Tverts[i].x, this->Tverts[i].y, 0.0);
				}
				glEnd();
			}
			else {
				glBegin(GL_TRIANGLES);
				for(unsigned i=0; i < tris.size(); i++) {
					glVertex3f(tris[i].x, tris[i].y, 0.0);
				}
				glEnd();
				if(this->type == TRIROID && this->clipped == 0) {
					glBegin(GL_LINES);
						glVertex3f(this->Tverts[0].x, this->Tverts[0].y, 0.0);
						glVertex3f(this->pos.x, this->pos.y, 0.0);
						glVertex3f(this->Tverts[1].x, this->Tverts[1].y, 0.0);
						glVertex3f(this->pos.x, this->pos.y, 0.0);
						glVertex3f(this->Tverts[2].x, this->Tverts[2].y, 0.0);
						glVertex3f(this->pos.x, this->pos.y, 0.0);
					glEnd();
				}
			}
			break;
		case FILLED:
			// draw the asteroid
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_TRIANGLES);
			for(unsigned i=0; i < tris.size(); i++) {
				glVertex3f(tris[i].x, tris[i].y, 0.0);
			}
			glEnd();
			break;
		default:
			break;
	}
}

