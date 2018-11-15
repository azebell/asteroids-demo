
/// Generating circle points and arcs.

#ifndef CIRCLE_H
#define CIRCLE_H

#include "vec.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/////////////////////////////////////////////////
// Generate a list of vertices along a circle centered at
// point c with radius r, having d points per octant.
// C function requires vector array to have size
// at least 8*d.
/////////////////////////////////////////////////
void gen_circle(vec3 c, float r, int d, vec3 *p);

#ifdef __cplusplus
}

#include <vector>

// wrapper for gen_circle function 
std::vector<vec3> gen_circle(vec3 c, float r, int d);

/////////////////////////////////////////////////
// Generate a list of vertices along an arc from two points
// defining a chord of a circle. The two points form a 
// counterclockwise arc of angle theta, with each octant of
// the circle that owns the arc having d points.
// The angle theta is in degrees, being between 1 and 360.
/////////////////////////////////////////////////
std::vector<vec3> arc(vec3 p1, vec3 p2, float theta, int d);

#endif // __cplusplus

#endif // CIRCLE_H

