
#include "vec.h"
#include <math.h>

float* vec3AsArray(vec3 *a) {
	return &a->x;
}

vec3 vec3Scale(vec3 a, float s) {
	return (vec3) {a.x*s, a.y*s, a.z*s};
}

float vec3Mag(vec3 a) {
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

vec3 vec3Unit(vec3 a) {
	float m = vec3Mag(a);
	return (vec3) {a.x/m, a.y/m, a.z/m};
}

float vec3Dot(vec3 a, vec3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

vec3 vec3Cross(vec3 a, vec3 b) {
	vec3 result = {
		a.y*b.z - b.y*a.z,
		b.x*a.z - a.x*b.z,
		a.x*b.y - b.x*a.y
	};
	return result;
}

vec3 vec3Sum(vec3 a, vec3 b) {
	return (vec3) {a.x+b.x, a.y+b.y, a.z+b.z};
}

vec3 vec3Diff(vec3 a, vec3 b) {
	return (vec3) {a.x-b.x, a.y-b.y, a.z-b.z};
}

vec3 operator +(vec3 a, vec3 b) {return vec3Sum(a,b);};
vec3 operator -(vec3 a, vec3 b) {return vec3Diff(a,b);};
vec3 operator -(vec3 a) {return {-a.x, -a.y, -a.z};};
vec3 operator *(float s, vec3 b) {return vec3Scale(b,s);};
float operator *(vec3 a, vec3 b) {return vec3Dot(a,b);};

