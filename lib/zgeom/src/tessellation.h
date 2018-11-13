
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

// return a list of triangle indices that refer to 
// points in 'vertices'
// (3 indices form a triangle)
std::vector<int> triangulate(std::vector<vec3> vertices, int CCW);

// triangulate list of vertices and return the tris
std::vector<vec3> triangulate_verts(std::vector<vec3> vertices, int CCW);

// return a list of triangle vertices specified by indices
std::vector<vec3> tris_from_indices(std::vector<int> indices, std::vector<vec3> vertices);

#endif // __cplusplus

#endif // TESSELLATION_H

