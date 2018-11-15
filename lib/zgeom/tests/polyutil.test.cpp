
#include "catch.hpp"
#include "zgeom.h"

TEST_CASE( "point in polygon", "[polyutil]" ) {

	vec3 a = {0.0,0.0,0.0};
	vec3 b = {1.0,0.0,0.0};
	vec3 c = {1.0,1.0,0.0};
	vec3 d = {0.0,1.0,0.0};
	vec3 p1 = {0.75,0.1,0.0};
	vec3 p2 = {0.25,0.75,0.0};
	vec3 p3 = {10.25,0.75,0.0};

	SECTION("point in triangle") {
		REQUIRE( point_in_triangle(p1,a,b,c) != 0 );
		REQUIRE( point_in_triangle(p2,a,b,c) == 0 );
		REQUIRE( point_in_triangle(p3,a,b,c) == 0 );
	}
	SECTION("point in polygon") {
		std::vector<vec3> poly = {a,b,c,d};
		vec3 *polyarray = &poly[0];
		int N = poly.size();

		REQUIRE( point_in_poly(p1,polyarray,N) != 0 );
		REQUIRE( point_in_poly(p2,polyarray,N) != 0 );
		REQUIRE( point_in_poly(p3,polyarray,N) == 0 );
	}

}

