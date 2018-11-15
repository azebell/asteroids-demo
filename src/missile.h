#include "vec.h"

#ifndef MISSILE_H
#define MISSILE_H

// Defines a missile as a line between two points with a set scalar velocity
struct missile {
	vec3 p1; // Defines p2 as an offset from P1
	vec3 p2 = { p1.x+5, p1.y, p1.Z };
	// TODO: Offset needs to be integrated with the ship's rotation angle
	float velocity; /* Scalar Velocity Value */
};

#endif
