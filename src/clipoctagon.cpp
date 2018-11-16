/*
#include <cmath>	//***moved to includes.h
*/

//#define PI 3.14159265359		//***moved to constants.h

#include "includes.h"
#include "structs.h"
#include "constants.h"
#include "clipoctagon.h"

vector<vector3D> genOctagon(float cx, float cy, float radius) {
	float step = PI/4.0;
	float ang = PI/8.0;
	vector<vector3D> result;
	for(int i=0; i<8; i++) {
		result.push_back(vector3D(cx + (float)cos(ang)*radius, 
					cy + (float)sin(ang)*radius, 0));
		ang += step;
	}
	return result;
}

