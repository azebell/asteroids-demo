
#include "catch.hpp"
#include "zgeom.h"
#include <stdio.h>

TEST_CASE( "line intersections", "[intersect]" ) {

	vec3 h1 = {0.0,0.0,0.0};
	vec3 h2 = {10.0,0.0,0.0};
	vec3 v1 = {5.0,0.0,0.0};
	vec3 v2 = {5.0,10.0,0.0};
	vec3 a1 = {1.0,1.0,0.0};
	vec3 a2 = {2.0,2.0,0.0};
	vec3 p1 = {1.0,2.0,0.0};
	vec3 p2 = {2.0,3.0,0.0};
	vec3 c1 = {1.0,3.0,0.0};
	vec3 c2 = {2.0,2.0,0.0};
	vec3 i, v;

	SECTION("intersecting lines HV") {
		REQUIRE( intersect_ll(h1, h2, v1, v2, &i) != 0 );
		v = {5.0,0.0,0.0};
		REQUIRE( i.x == v.x );
		REQUIRE( i.y == v.y );
		REQUIRE( i.z == v.z );
	}
	SECTION("intersecting lines SH") {
		REQUIRE( intersect_ll(a1, a2, h1, h2, &i) != 0 );
		v = {0.0,0.0,0.0};
		REQUIRE( i.x == v.x );
		REQUIRE( i.y == v.y );
		REQUIRE( i.z == v.z );

	}
	SECTION("parallel lines") {
		REQUIRE( intersect_ll(a1, a2, p1, p2, &i) == 0 );
	}
	SECTION("intersecting lines slant") {
		REQUIRE( intersect_ll(a1, a2, c1, c2, &i) != 0 );
		v = {2.0,2.0,0.0};
		REQUIRE( i.x == v.x );
		REQUIRE( i.y == v.y );
		REQUIRE( i.z == v.z );
	}
}

TEST_CASE( "line segment intersections", "[intersect]" ) {

	vec3 a1 = {0.0,0.0,0.0};
	vec3 a2 = {10.0,0.0,0.0};
	vec3 b1 = {1.0,5.0,0.0};
	vec3 b2 = {1.0,1.0,0.0};
	vec3 c1 = {1.0,5.0,0.0};
	vec3 c2 = {1.0,-1.0,0.0};
	vec3 i, v;

	SECTION("non-intersecting line segments") {
		REQUIRE( intersect_ss(a1, a2, b1, b2, &i) == 0 );
	}
	SECTION("intersecting line segments") {
		REQUIRE( intersect_ss(a1, a2, c1, c2, &i) != 0 );
		v = {1.0,0.0,0.0};
		REQUIRE( i.x == v.x );
		REQUIRE( i.y == v.y );
		REQUIRE( i.z == v.z );
	}

	vec3 p1 = {1.0, 2.0, 0.0};
	vec3 p2 = {2.0, 0.0, 0.0};
	SECTION("line segment tips") {
		vec3 q1 = {2.0, 0.0, 0.0};
		vec3 q2 = {4.0, 9.0, 0.0};
		REQUIRE( intersect_ss(p1, p2, q1, q2, &i) < 0 );
		v = {2.0,0.0,0.0};
		REQUIRE( i.x == v.x );
		REQUIRE( i.y == v.y );
		REQUIRE( i.z == v.z );
	}
	SECTION("line segments not tips") {
		vec3 r1 = {1.0, 0.0, 0.0};
		vec3 r2 = {2.0, 2.0, 0.0};
		REQUIRE( intersect_ss(p1, p2, r1, r2, &i) > 0 );
		v = {1.5,1.0,0.0};
		REQUIRE( i.x == v.x );
		REQUIRE( i.y == v.y );
		REQUIRE( i.z == v.z );
	}

}

TEST_CASE( "point segment intersection", "[intersect]" ) {
	vec3 a1 = {0.0,0.0,0.0};
	vec3 a2 = {10.0,0.0,0.0};
	vec3 b1 = {1.0,1.0,0.0};
	vec3 b2 = {1.0,1.0,0.0};
	vec3 i;

	// point line should not intersect line or segment
	REQUIRE( intersect_ss(a1, a2, b1, b2, &i)==0 );
	REQUIRE( intersect_ls(a1, a2, b1, b2, &i)==0 );
	REQUIRE( intersect_ll(a1, a2, b1, b2, &i)==0 );
}

TEST_CASE( "line and segment intersections", "[intersect]" ) {
	vec3 a1 = {0.0,0.0,0.0};
	vec3 a2 = {3.0,3.0,0.0};

	vec3 b1 = {1.0,3.0,0.0};
	vec3 b2 = {2.0,2.0,0.0};
	vec3 c1 = {1.0,5.0,0.0};
	vec3 c2 = {2.0,4.0,0.0};
	vec3 d1 = {3.0,5.0,0.0};
	vec3 d2 = {5.0,3.0,0.0};

	vec3 i;

	REQUIRE( intersect_ls(a1, a2, b1, b2, &i) < 0);
	REQUIRE( i.x==2.0 );
	REQUIRE( i.y==2.0 );

	REQUIRE( intersect_ls(a1, a2, c1, c2, &i) == 0);

	REQUIRE( intersect_ls(a1, a2, d1, d2, &i) > 0);
	REQUIRE( i.x==4.0 );
	REQUIRE( i.y==4.0 );

}

TEST_CASE( "point on line", "[intersect]" ) {
	vec3 a1 = {0.0,0.0,0.0};
	vec3 a2 = {3.0,3.0,0.0};

	vec3 p1 = {2.0,2.0,0.0};
	vec3 p2 = {4.0,4.0,0.0};
	vec3 p3 = {-1.0,-1.0,0.0};
	vec3 p4 = {5.0,4.0,0.0};

	REQUIRE( point_on_line(p1, a1, a2)==1 );
	REQUIRE( point_on_line(p2, a1, a2)==-1 );
	REQUIRE( point_on_line(p3, a1, a2)==-1 );
	REQUIRE( point_on_line(p4, a1, a2)==0 );

	// line in reverse
	REQUIRE( point_on_line(p1, a2, a1)==1 );
	REQUIRE( point_on_line(p2, a2, a1)==-1 );
	REQUIRE( point_on_line(p3, a2, a1)==-1 );
	REQUIRE( point_on_line(p4, a2, a1)==0 );

}

TEST_CASE( "point on horizontal line", "[intersect]" ) {
	vec3 a1 = {2.0,2.0,0.0};
	vec3 a2 = {5.0,2.0,0.0};

	vec3 p1 = {3.0,2.0,0.0};

	REQUIRE( point_on_line(p1, a1, a2)==1 );
}
