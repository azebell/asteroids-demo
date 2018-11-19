
#include "asteroid.h"
#include "zgeom.h"
#include <vector>

std::vector<Asteroid> bustTris(Asteroid A) {
	std::vector<Asteroid> result;

	// get the unclipped, rotated verts
	mat4 T = mat4Identity();
	mat4RotateZ(&T, A.theta);
	A.Tverts = applyTransform(T, A.verts);
	// get each triangle of the asteroid
	std::vector<vec3> tris = triangulate(A.Tverts, CCW_WINDING);

	// For each triangle, find the centroid
	// and move the triangle to the model-space
	// origin.
	// Using the offset to figure out its previous
	// position, and set the new asteroid's pos 
	// to that world position.
	vec3 centroid;
	for(unsigned i=0; i<tris.size(); i+=3) {
		centroid.x = (tris[i].x + tris[i+1].x + tris[i+2].x) / 3.0;
		centroid.y = (tris[i].y + tris[i+1].y + tris[i+2].y) / 3.0;

		std::vector<vec3> vertices;
		vertices.push_back( (vec3) {
			tris[i].x - centroid.x, tris[i].y - centroid.y 
		});
		vertices.push_back( (vec3) {
			tris[i+1].x - centroid.x, tris[i+1].y - centroid.y 
		});
		vertices.push_back( (vec3) {
			tris[i+2].x - centroid.x, tris[i+2].y - centroid.y 
		});
		vec3 newPos = A.pos + centroid;
		Asteroid tmp(newPos, vertices);
		tmp.vel = vec3Mag(tmp.vel) * vec3Unit(centroid);
		tmp.type = Asteroid::TRIROID;
		tmp.update();
		result.push_back(tmp);
	}

	return result;
}

