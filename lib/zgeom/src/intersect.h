
/// Line intersection functions

#ifndef INTERSECT_H
#define INTERSECT_H

#include "vec.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/////////////////////////////////////////////////
// Converts two points into an
// equation for a line in standard form.
// Stores A, B, C of line equation in 
// a 3D vector.
/////////////////////////////////////////////////
vec3 line_coords(vec3 p1, vec3 p2);

/////////////////////////////////////////////////
// Checks if point p lies on line from a1 to a2.
// Returns:
//    1 if on line segment
//   -1 if on line
//    0 if not on line nor segment
/////////////////////////////////////////////////
int point_on_line(vec3 p, vec3 a1, vec3 a2);

/////////////////////////////////////////////////
// Finds the intersection point of two lines.
// Returns 1 if intersection, 0 if not.
// Assigns intersection point to vector i.
// If no intersection, does not modify i.
/////////////////////////////////////////////////
int intersect_ll(vec3 a1, vec3 a2, vec3 b1, vec3 b2, vec3 *i);

/////////////////////////////////////////////////
// Finds the intersection point of two line segments.
// Returns:
//    1 if intersection
//   -1 if intersect at an endpoint
//    0 if no intersection
// Assigns intersection point to vector i.
// If no intersection, does not modify i.
/////////////////////////////////////////////////
int intersect_ss(vec3 a1, vec3 a2, vec3 b1, vec3 b2, vec3 *i);

/////////////////////////////////////////////////
// Finds the intersection point of line and segment.
// Returns:
//    1 if intersection
//   -1 if intersect at an endpoint
//    0 if no intersection
// Assigns intersection point to vector i.
// If no intersection, does not modify i.
/////////////////////////////////////////////////
int intersect_ls(vec3 a1, vec3 a2, vec3 b1, vec3 b2, vec3 *i);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // INTERSECT_H

