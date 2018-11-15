
/// Vector utilities: vec3 struct and common vector operations

#ifndef VEC_H
#define VEC_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct vec3 {
	float x;
	float y;
	float z;
} vec3;

float* vec3AsArray(vec3 *a);

vec3 vec3Scale(vec3 a, float s);
float vec3Mag(vec3 a);
vec3 vec3Unit(vec3 a);
float vec3Dot(vec3 a, vec3 b);
vec3 vec3Cross(vec3 a, vec3 b);
vec3 vec3Sum(vec3 a, vec3 b);
vec3 vec3Diff(vec3 a, vec3 b);

#ifdef __cplusplus
}

vec3 operator +(vec3 a, vec3 b);
vec3 operator -(vec3 a, vec3 b);
vec3 operator -(vec3 a);
vec3 operator *(float s, vec3 b);
float operator *(vec3 a, vec3 b);

#endif // __cplusplus

#endif // VEC_H

