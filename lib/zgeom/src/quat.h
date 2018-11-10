
/// Quaternion struct and common functions

#ifndef QUAT_H
#define QUAT_H

#include "vec.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct quat4 {
	float w;
	vec3 v;
} quat4;

quat4 quat4AxisAngle(vec3 axis, float theta);

quat4 quat4Unit(quat4 Q);

quat4 quat4Scale(float s, quat4 Q);
quat4 quat4Sum(quat4 A, quat4 B);
quat4 quat4Diff(quat4 A, quat4 B);
quat4 quat4Mult(quat4 A, quat4 B);

////////////////////////////////////////////////
// SLERP (spherical linear interpolation)
// Given an interpolation parameter between
// 0 and 1, returns a quaternion interpolated
// between quaternions A and B.
// https://en.wikipedia.org/wiki/Slerp
////////////////////////////////////////////////
quat4 quat4Slerp(quat4 A, quat4 B, float t);

#ifdef __cplusplus
}

quat4 operator *(float A, quat4 B);
quat4 operator +(quat4 A, quat4 B);
quat4 operator -(quat4 A, quat4 B);
quat4 operator *(quat4 A, quat4 B);

#endif // __cplusplus

#endif // QUAT_H

