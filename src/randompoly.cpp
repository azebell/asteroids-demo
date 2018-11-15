
#include "randompoly.h"
#include <cmath>

#define PI 3.14159265359

float rand_range(float range) {
	float r = ((rand()%100)/50.0) - 1.0;
	return r*range;
}

std::vector<vec3> randomPoly(float r, int p) {
	std::vector<vec3> vertices;
	float iwx = 1 - rand_range(0.5), wx = iwx;
	float iwy = 1 - rand_range(0.5), wy = iwy;
	for(int i=0; i<p; i++) {
		vertices.push_back( {
			wx*r* (float)cos(i*2*PI/p),
			wy*r* (float)sin(i*2*PI/p)
		});

		wx = 1 - rand_range(0.5);
		wy = 1 - rand_range(0.5);
	}

	return vertices;
}

