#include "spaceship.h"
#include <math.h>
#include <cstdlib>
#include "glFuncs.h"

Spaceship::Spaceship() : Spaceship({0.0,0.0,0.0}) {
}

// creating Spaceship with specified geometry
Spaceship::Spaceship(vec3 position) : pos(position) {
	this->vel = {0.0,0.0,0.0};
	this->verts.push_back( {   0.0,   0.0 });
	this->verts.push_back( { -10.0,  10.0 });
	this->verts.push_back( {  20.0,   0.0 });
	this->verts.push_back( { -10.0, -10.0 });
	this->Tverts = verts;
}

void Spaceship::setRotationAngle(float angle){ 
	if(alpha == 0)
		this -> alpha = angle;
	else{
		alpha = 0;
		angle = 0;
	}
}

// update Spaceship with new rotation direction
void Spaceship::update() {
	
	this->theta += this->alpha;

	this->transform = mat4Identity();
	mat4RotateZ(&this->transform, this->theta); 
	mat4Translate(&this->transform, this->pos); 
	this->Tverts = applyTransform(this->transform, this->verts);

	this -> alpha = 0;
}


void Spaceship::render() {
	// draw the Spaceship
	glBegin(GL_POLYGON);
	for(unsigned i=0; i < this->Tverts.size(); i++) {
		glVertex3f(this->Tverts[i].x, this->Tverts[i].y, 0.0);
	}
	glEnd();
}

