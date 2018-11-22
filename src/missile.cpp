#include <cstdlib>
#include "glFuncs.h"
#include "zgeom.h"
#include "missile.h"
#include "constants.h"

/* Defines a missile as a line spawned from the center of the window which
 * Is rotated by the same degree as the player ship
*/
missile::missile(float ShipTheta) {
	this->vel = 25.0; // Missile travels at a set scalar velocity
	this->theta = ShipTheta;
	this->verts.push_back( {WINDOW_MAX_X/2, WINDOW_MAX_X/2, 0.0} );
	this->verts.push_back( {WINDOW_MAX_X/2, WINDOW_MAX_X/2, 0.0} );
	this->Tverts = verts;
}

// Transforms the missile
void missile::transformVerts() {
	this->transform = mat4Identity();
	mat4RotateZ(&this->transform, this->theta);
	mat4Translate(&this->transform, this->pos);
	this->Tverts = applyTransform(this->transform, this->verts);
}

// Clips the missile against the clip boundry
void missile::clip(std::vector<vec3> clipper) {
	this->Tverts = clip_sh(this->Tverts, clipper);
}

// Updates the coordinates of the missile
void missile::update() {
	this->pos.x += this->vel.x;
	this->pos.y += this->vel.y;
	this->pos.z += this->vel.z;

	this->transformVerts();
}

// Draws the missile to screen
void missile::render() {
	glBegin(GL_LINE);
	glVertex3f(this->Tverts[0].x, this->Tverts[1].y, 0.0);
	glVertex3f(this->Tverts[0].x, this->Tverts[1].y, 0.0);
	glEnd();
}
