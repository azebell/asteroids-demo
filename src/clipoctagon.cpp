
#include "clipoctagon.h"
#include <cmath>

std::vector<vec3> genOctagon(float cx, float cy, float radius) {
	float step = M_PI/4.0;
	float ang = M_PI/8.0;
	std::vector<vec3> result;
	for(int i=0; i<8; i++) {
		result.push_back({
			cx + (float)cos(ang)*radius,
			cy + (float)sin(ang)*radius
		});
		ang += step;
	}
	return result;
}

