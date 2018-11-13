
#include "catch.hpp"
#include "zgeom.h"

#define PI 3.14159265358979323846264338327950288

TEST_CASE( "quat rotation", "[quat]" ) {
	vec3 p = {1,0,0};
	vec3 pT;
	vec3 target = {0,1,0};

	quat4 rot = quat4AxisAngle({0,0,1}, PI/2.0);
	mat4 T = quat4ToMat4(rot);
	applyTransform(T, &p, &pT, 1);

	CHECK( pT.x==target.x );
	CHECK( pT.y==target.y );
	CHECK( pT.z==target.z );
}

TEST_CASE( "multi quat rotation", "[quat]" ) {
	vec3 p = {1,0,0};
	vec3 pT;
	vec3 target = {0,1,0};

	quat4 rot1 = quat4AxisAngle({0,1,0}, PI/2.0);
	quat4 rot2 = quat4AxisAngle({1,0,0}, PI/2.0);
	quat4 rot = quat4Mult(rot2, rot1);
	mat4 T = quat4ToMat4(rot);
	applyTransform(T, &p, &pT, 1);

	CHECK( pT.x==target.x );
	CHECK( pT.y==target.y );
	CHECK( pT.z==target.z );
}

