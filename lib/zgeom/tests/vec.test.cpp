
#include "catch.hpp"
#include "zgeom.h"

TEST_CASE( "vec3 as array", "[vec]" ) {

	// If a struct contains members of the same type, 
	// we can treat it like an array if we need to 
	// by making a pointer to first struct member.

	vec3 a = {1.0,2.0,3.0};
	float *v = &a.x;
	float *va = vec3AsArray(&a);

	SECTION("vec3 bracket indexing") {
		CHECK( v[0]==1.0 );
		CHECK( v[1]==2.0 );
		CHECK( v[2]==3.0 );
		CHECK( va[0]==1.0 );
		CHECK( va[1]==2.0 );
		CHECK( va[2]==3.0 );
	}
	SECTION("vec3 pointer arithmetic") {
		CHECK( *(v+0)==1.0 );
		CHECK( *(v+1)==2.0 );
		CHECK( *(v+2)==3.0 );
		CHECK( *(va+0)==1.0 );
		CHECK( *(va+1)==2.0 );
		CHECK( *(va+2)==3.0 );
	}

}

