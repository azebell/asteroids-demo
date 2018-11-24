
#include "missile.h"
#include "zgeom.h"
#include "glFuncs.h"
#include <cmath> 

/* Defines a missile as a line spawned from the center of the window which
 * Is rotated by the same degree as the player ship
*/
Missile::Missile(vec3 position, float angle)
: pos(position), theta(angle) {
	vec3 velocity = {
		(float) cos(this->theta),
		(float) sin(this->theta)
	};
	this->vel = 5*vec3Unit(velocity);
	this->verts.push_back( { 0.0, 0.0, 0.0 } );
	this->verts.push_back( { 10.0, 0.0, 0.0 } );
	this->Tverts = verts;
}

// Transforms the missile
void Missile::transformVerts() {
	this->transform = mat4Identity();
	mat4RotateZ(&this->transform, this->theta);
	mat4Translate(&this->transform, this->pos);
	this->Tverts = applyTransform(this->transform, this->verts);
}

// Updates the coordinates of the missile
void Missile::update() {
	this->pos.x += this->vel.x;
	this->pos.y += this->vel.y;
	this->pos.z += this->vel.z;

	this->transformVerts();
}

// Draws the missile to screen
void Missile::render() {
	glBegin(GL_LINES);
		glVertex3f(this->Tverts[0].x, this->Tverts[0].y, 0.0);
		glVertex3f(this->Tverts[1].x, this->Tverts[1].y, 0.0);
	glEnd();
}
