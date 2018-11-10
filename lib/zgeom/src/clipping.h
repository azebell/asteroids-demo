
/// Polygon clipping functions.

#ifndef CLIPPING_H
#define CLIPPING_H

#include "vec.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __cplusplus
}

#include <vector>

/////////////////////////////////////////////////
// Clips a polygon P against a mask polygon
// M using the Sutherland-Hodgman clipping
// algorithm.
// M must be a simple polygon.
/////////////////////////////////////////////////
std::vector<vec3> clip_sh(std::vector<vec3> P, std::vector<vec3> M);

#endif // __cplusplus

#endif // CLIPPING_H

