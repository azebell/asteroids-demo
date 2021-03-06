
#include "polyutil.h"
#include "intersect.h"
#include "util.h"

//////////////////////////////////////////////////////
// If a,b,c are in a counterclockwise order,
// then the area is positive. So taking in 3 points
// from a shape being traversed counterclockwise 
// and checking the sign of the area will show
// if it is convex.
// The area of the triangle using this method
// is equivalent to the cross product method
// since we are working in 2D space.
// Reference:
//   Shoelace formula
//   http://www.mathopenref.com/coordtrianglearea.html
//////////////////////////////////////////////////////
float tri_area(vec3 a, vec3 b, vec3 c) {
	float area = 0.0;
	area += a.x*(b.y-c.y);
	area += b.x*(c.y-a.y);
	area += c.x*(a.y-b.y);
	return area/2.0;
}

//////////////////////////////////////////////////////
// http://geomalgorithms.com/a03-_inclusion.html
// Returns:
//   >0 a is left
//   =0 a is on line
//   <0 a is right
//////////////////////////////////////////////////////
float pointIsLeft(vec3 a, vec3 b, vec3 c) {
	return ( (c.x - b.x) * (a.y - b.y) - (a.x -  b.x) * (c.y - b.y) );
}

//////////////////////////////////////////////////////
// determine if point is in triangle
// using the area (or cross product).
// if all z components have the same sign, then the 
// point lies within the triangle.
//////////////////////////////////////////////////////
int point_in_triangle(vec3 p, vec3 a, vec3 b, vec3 c) {
	float ABP = pointIsLeft(a,b,p);
	float BCP = pointIsLeft(b,c,p);
	float CAP = pointIsLeft(c,a,p);
	return (ABP>0 && BCP>0 && CAP>0) || (ABP<0 && BCP<0 && CAP<0);
}

//////////////////////////////////////////////////////
// http://geomalgorithms.com/a03-_inclusion.html
// Winding number test for a point in a polygon.
// Return:  wn = the winding number (=0 only when P is outside)
//////////////////////////////////////////////////////
int point_in_poly(vec3 p, vec3 *poly, unsigned N) {
	int wn = 0;
	int curr, next;

	curr = N-1;
	for(unsigned i=0; i<N; i++) {
		next = i;
		if(poly[curr].y <= p.y) {          // start y <= P.y
			if(poly[next].y > p.y)      // an upward crossing
				if(pointIsLeft(poly[curr], poly[next], p) > 0)  // P left of  edge
					wn++;            // have  a valid up intersect
		}
		else {                        // start y > P.y (no test needed)
			if(poly[next].y <= p.y)     // a downward crossing
				if(pointIsLeft(poly[curr], poly[next], p) < 0)  // P right of  edge
					wn--;            // have  a valid down intersect
		}
		curr = next;
	}
	return wn;
}

int point_in_poly(vec3 p, std::vector<vec3> poly) {
	return point_in_poly(p, &poly[0], poly.size());
}

int poly_intersect(std::vector<vec3> A, std::vector<vec3> B) {
	if(A.size()==0 || B.size()==0)
		return 0;
	vec3 intersection;
	vec3 a1, a2, b1, b2;
	a1 = A[A.size()-1];
	for(unsigned i=0; i<A.size(); i++) {
		a2 = A[i];
		b1 = B[B.size()-1];
		for(unsigned j=0; j<B.size(); j++) {
			b2 = B[j];
			//if(intersect_ss(A[i], A[i+1], B[j], B[j+1], &intersection)) {
			if(intersect_ss(a1, a2, b1, b2, &intersection)) {
				return 1;
			}
			b1 = b2;
		}
		a1 = a2;
	}
	return 0;
}

