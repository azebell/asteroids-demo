
#include "polyutil.h"
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
	return ( (b.x - c.x) * (a.y - c.y) - (a.x -  c.x) * (b.y - c.y) );
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
int point_in_poly(vec3 p, vec3 *poly, unsigned int N) {
	int wn = 0;
	//int N = poly.size();
	int curr, next;

	/*
	for(int i=0; i<N; i++) {
		curr = positive_modulo(i,N);
		next = positive_modulo(i+1,N);
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
	}
	return wn;
	*/

	for(unsigned int i=0; i<N; i++) {
		curr = positive_modulo(i,N);
		next = positive_modulo(i+1,N);
		if(poly[curr].x >= p.x || poly[next].x >= p.x) {
			if(poly[curr].y <= p.y && poly[next].y > p.y) {
				wn++;
			}
			else if(poly[next].y <= p.y && poly[curr].y > p.y) {
				wn--;
			}
		}
	}
	return wn;
}

int point_in_poly(vec3 p, std::vector<vec3> poly) {
	return point_in_poly(p, &poly[0], poly.size());
}

