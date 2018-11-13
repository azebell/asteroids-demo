
/// Common 3D transformation functions

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec.h"
#include "mat.h"
#include "quat.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void mat4Translate(mat4 *m, vec3 translate);
void mat4Scale(mat4 *m, vec3 scale);
void mat4RotateX(mat4 *m, float theta);
void mat4RotateY(mat4 *m, float theta);
void mat4RotateZ(mat4 *m, float theta);
void mat4Rotate(mat4 *m, vec3 axis, float theta);

mat4 mat4LookAt(vec3 target, vec3 pos, vec3 up);

mat4 quat4ToMat4(quat4 Q);
void applyTransform(mat4 T, vec3 *p, vec3 *pT, int N);

#ifdef __cplusplus
}

#include <vector>
std::vector<vec3> applyTransform(mat4 T, std::vector<vec3> p);

std::vector<vec3> operator *(mat4 T, std::vector<vec3> p);
mat4 operator *(quat4 Q, mat4 T);
mat4 operator *(mat4 T, quat4 Q);

#endif // __cplusplus

#endif // TRANSFORM_H

