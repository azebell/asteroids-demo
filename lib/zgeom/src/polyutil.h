
/// Common polygon functions.
/// Point inclusion/exclusion.

#ifndef POLYUTIL_H
#define POLYUTIL_H

#include "vec.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//////////////////////////////////////////////////////
// http://geomalgorithms.com/a03-_inclusion.html
// Returns:
//   >0 a is left
//   =0 a is on line
//   <0 a is right
//////////////////////////////////////////////////////
float pointIsLeft(vec3 a, vec3 b, vec3 c);

float tri_area(vec3 a, vec3 b, vec3 c);

int point_in_triangle(vec3 p, vec3 a, vec3 b, vec3 c);

int point_in_poly(vec3 p, vec3 *poly, unsigned N);

#ifdef __cplusplus
}

#include <vector>

int point_in_poly(vec3 p, std::vector<vec3> poly);

int poly_intersect(std::vector<vec3> A, std::vector<vec3> B);

#endif // __cplusplus

#endif // POLYUTIL_H

