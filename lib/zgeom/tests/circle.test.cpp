
#include "catch.hpp"
#include "zgeom.h"

TEST_CASE( "circle no duplicated points", "[circle]" ) {

	std::vector<vec3> p = gen_circle({0,0,0}, 50.0, 25);
	int N = p.size();
	int dupes = 0;
	std::vector<vec3> d;

	if(p[0].x==p[N-1].x)
		if(p[0].y==p[N-1].y)
			if(p[0].z==p[N-1].z) {
				dupes++;
				d.push_back(p[0]);
			}
	for(int i=0; i<N-1; i++) {
		if(p[i].x==p[i+1].x)
			if(p[i].y==p[i+1].y)
				if(p[i].z==p[i+1].z) {
					dupes++;
					d.push_back(p[i]);
				}
	}

	REQUIRE( dupes==0 );
}

