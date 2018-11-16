
/// Tessellation functions (triangulation) using ear-clipping algorithm

#ifndef TESSELLATION_H
#define TESSELLATION_H

#include "vec.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// return number of triangles that will be generated
// from tessellating a polygon with N points
unsigned int tris_in_poly(unsigned int N);

#ifdef __cplusplus
}

#include <vector>

// triangulate list of vertices with 
// the earclipping algorithm and return the tris
std::vector<vec3> triangulate(std::vector<vec3> vertices, int CCW);

#endif // __cplusplus

#endif // TESSELLATION_H

