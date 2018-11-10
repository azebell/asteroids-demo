
#include "intersect.h"

/////////////////////////////////////////////////
// Converts two points into an
// equation for a line in standard form.
// Stores A, B, C of line equation in 
// a 3D vector.
/////////////////////////////////////////////////
vec3 line_coords(vec3 p1, vec3 p2) {
	float A = p2.y - p1.y;
	float B = p1.x - p2.x;
	float C = p1.y*p2.x - p1.x*p2.y;
	vec3 u = {A,B,C};
	return u;
}

/////////////////////////////////////////////////
// Checks if point p lies on line from a1 to a2.
// Returns:
//    1 if on line segment
//   -1 if on line
//    0 if not on line nor segment
/////////////////////////////////////////////////
int point_on_line(vec3 p, vec3 a1, vec3 a2) {
	vec3 L = line_coords(a1, a2);
	if(p.x*L.x + p.y*L.y + L.z != 0)
		return 0;
	if((p.x < a1.x && p.x < a2.x) || (p.x > a1.x && p.x > a2.x))
		return -1;
	return 1;
}

/////////////////////////////////////////////////
// Finds the intersection point of two lines.
// Returns 1 if intersection, 0 if not.
// Assigns intersection point to vector i.
// If no intersection, does not modify i.
/////////////////////////////////////////////////
int intersect_ll(vec3 a1, vec3 a2, vec3 b1, vec3 b2, vec3 *i) {

	// Given two infinite lines in 2D space
	// that are standard form (Ax + By + C = 0)
	// then these lines can be treated as vectors
	// where U1 = <A,B,C> and U2 formed likewise.
	// The intersection then is at U1 x U2 where
	// the resulting vector's C != 0.
	// We transform the map the intersection
	// point back into 2D by dividing the
	// components by the homogeneous coordinate.

	vec3 u1 = line_coords(a1, a2);
	vec3 u2 = line_coords(b1, b2);

	vec3 p = vec3Cross(u1, u2);
	if(p.z==0)
		return 0;
	p.x = p.x/p.z;
	p.y = p.y/p.z;
	p.z = 0.0;
	*i = p;
	return 1;
}

/////////////////////////////////////////////////
// Finds the intersection point of two line segments.
// Returns:
//    1 if intersection
//   -1 if intersect at an endpoint
//    0 if no intersection
// Assigns intersection point to vector i.
// If no intersection, does not modify i.
/////////////////////////////////////////////////
int intersect_ss(vec3 a1, vec3 a2, vec3 b1, vec3 b2, vec3 *i) {

	float ua, ub;
	float denom;

	denom = (a2.x-a1.x)*(-b2.y+b1.y) - (-b2.x+b1.x)*(a2.y-a1.y);
	ua = (b1.x-a1.x)*(-b2.y+b1.y) - (-b2.x+b1.x)*(b1.y-a1.y);
	ub = (a2.x-a1.x)*(b1.y-a1.y) - (b1.x-a1.x)*(a2.y-a1.y);
	ua /= denom;
	ub /= denom;

	if(ua<0.0 || ua>1.0 || ub<0.0 || ub>1.0)
		return 0;
	i->x = a1.x + ua*(a2.x - a1.x);
	i->y = a1.y + ua*(a2.y - a1.y);
	if(ua==0.0 || ua==1.0 || ub==0.0 || ub==0.0) // tip intersection
		return -1;
	return 1;
	
}

/////////////////////////////////////////////////
// Finds the intersection point of line and segment.
// Returns:
//    1 if intersection
//   -1 if intersect at an endpoint
//    0 if no intersection
// Assigns intersection point to vector i.
// If no intersection, does not modify i.
/////////////////////////////////////////////////
int intersect_ls(vec3 a1, vec3 a2, vec3 b1, vec3 b2, vec3 *i) {
	vec3 n = vec3Diff(a2,a1);
	n = {n.y, -n.x, 0.0};
	float d1 = vec3Dot(n, vec3Diff(b1, a1));
	float d2 = vec3Dot(n, vec3Diff(b2, a1));
	if( (d1>0 && d2 > 0) || (d1 < 0 && d2 < 0) )
		return 0;
	intersect_ll(a1, a2, b1, b2, i);
	if( d1==0 || d2==0 )
		return -1;
	return 1;

}

