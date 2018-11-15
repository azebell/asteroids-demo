
#include "catch.hpp"
#include "zgeom.h"

#define M_PI 3.14159265358979323846

TEST_CASE( "rotate about point", "[transform]" ) {
	vec3 p1 = {2,2,0};
	vec3 p2 = {5,2,0};
	vec3 seg = p2-p1;
	vec3 pivot = {3,2,0};

	mat4 T = mat4Identity();
	mat4Translate(&T, {-3, -2, 0}); // move pivot to the origin
	mat4Scale(&T, {1.75, 1.0, 1.0});
	mat4RotateZ(&T, M_PI/6.0);
	mat4Translate(&T, {3, 2, 0});

	std::vector<vec3> pts = {p1, p2};
	std::vector<vec3> ptsT = pts;
	applyTransform(T, &pts[0], &ptsT[0], pts.size());
	//std::vector<vec3> ptsT = applyTransform(T, pts);

	vec3 segT = ptsT[1]-ptsT[0];

	// check that original seg contains pivot
	REQUIRE( point_on_line(pivot, pts[0], pts[1])!=0 );
	// check that the length has changed accordingly
	REQUIRE( vec3Mag(segT)==1.75*vec3Mag(seg) );
	// check that transformed seg contains pivot
	REQUIRE( point_on_line(pivot, ptsT[0], ptsT[1])!=0 );
}

TEST_CASE( "function mapping", "[transform]" ) {

	mat4 T = mat4Identity();
	mat4Translate(&T, {70.0, -20.0, 0.0});
	mat4Scale(&T, {500.0/(50.0+70.0), 500.0/(125.0-20.0), 1.0});
	mat4Translate(&T, {100.0, 100.0, 0.0});

	vec3 p1 = {-70, 20, 0};
	vec3 p2 = {50, 125, 0};
	vec3 p3 = {-25, 100, 0};
	std::vector<vec3> pts = {p1, p2, p3};
	//std::vector<vec3> ptsT = pts;
	//applyTransform(T, &pts[0], &ptsT[0], pts.size());
	std::vector<vec3> ptsT = applyTransform(T, pts);

	REQUIRE( ptsT[0].x==100.0 );
	REQUIRE( ptsT[0].y==100.0 );
	REQUIRE( ptsT[1].x==600.0 );
	REQUIRE( ptsT[1].y==600.0 );
	REQUIRE( (int)ptsT[2].x==287 );
	REQUIRE( (int)ptsT[2].y==480 );
}

