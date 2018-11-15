
#include "clipping.h"
#include "intersect.h"
#include "polyutil.h"

/////////////////////////////////////////////////
// Clips a polygon P against a mask polygon
// M using the Sutherland-Hodgman clipping
// algorithm.
// M must be a simple polygon.
/////////////////////////////////////////////////
std::vector<vec3> clip_sh(std::vector<vec3> P, std::vector<vec3> M) {
	std::vector<vec3> output = P;
	int MASKSIZE = M.size();
	int POLYSIZE = P.size();
	int curr = MASKSIZE-1, next = 0;
	for(int i=0; i<MASKSIZE; i++) {
		next = i;
		vec3 c1 = M[curr], c2 = M[next];

		// set the current poly to be the output of 
		// the previous pass
		P = output;
		POLYSIZE = P.size();
		// clear the output for another pass
		output.clear();
		
		vec3 intersection;
		vec3 p1 = P[POLYSIZE-1];
		for(int k=0; k<POLYSIZE; k++) {
			vec3 p2 = P[k];
			if(pointIsLeft(p2, c1, c2) > 0) { // p2 inside the clip polygon
				if(pointIsLeft(p1, c1, c2) <= 0) { // point is outside clip polygon
					// push intersect point p1-p2 seg and c1-c2 line
					intersect_ls(c1, c2, p1, p2, &intersection);
					output.push_back(intersection);
				}
				output.push_back(p2);
			}
			else if(pointIsLeft(p1, c1, c2) > 0) { // p2 outside and p1 inside
				// push intersect point p1-p2 seg and c1-c2 line
				intersect_ls(c1, c2, p1, p2, &intersection);
				output.push_back(intersection);
			}
			p1 = p2;
		}
		curr = next;
	}

	return output;
}

