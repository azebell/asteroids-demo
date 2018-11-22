#include <cmath>
#define PI 3.14159265359
#include "clipoctagon.h"

vector<vec3> genOctagon(float cx, float cy, float radius) {
	float step = PI/4.0;
	float ang = PI/8.0;
	vector<vec3> result;
	for(int i=0; i<8; i++) {
		result.push_back(vec3(cx + (float)cos(ang)*radius, 
					cy + (float)sin(ang)*radius, 0));
		ang += step;
	}
	return result;
}
