
#include "tessellation.h"
#include "polyutil.h"
#include "util.h"

// return number of triangles that will be generated
// from tessellating a polygon with N points
unsigned int tris_in_poly(unsigned int N) {
	if(N>2)
		return N-2;
	return 0;
}

// return the index of the first valid ear
//int find_ear(const std::vector<vec3> &vertices, int CCW) {
int find_ear(const vec3 *vertices, unsigned int N, int CCW) {
	bool valid = true;
	int prev, next;
	for(unsigned int i=0; i<N; i++) {
		valid = true;
		prev = positive_modulo(i-1, N);
		next = positive_modulo(i+1, N);
		float area = tri_area(vertices[prev],vertices[i],vertices[next]); 
		//if(area == 0) {
		if(area < 3 && area > -3) { // heuristic for tessellating super thin ears
			return i;
		}
		if((area > 0.0 && CCW) || (area < 0.0 && !CCW)) {
			for(unsigned int k=0; k<N; k++) {
				if(point_in_triangle(vertices[k], vertices[prev], vertices[i], vertices[next])) {
					valid = false;
					break;
				}
			}
			if(valid) {
				return i;
			}
		}
	}
	return 0;
}

std::vector<int> triangulate(std::vector<vec3> vertices, int CCW) {
	int N = vertices.size();
	
	if(N < 3) {
		std::vector<int> empty;
		return empty;
	}
	else if(N == 3) {
		std::vector<int> indices = {0,1,2};
		return indices;
	}

	int ear, prev, next;
	std::vector<int> result;
	std::vector<int> indices;
	for(int i=0; i<N; i++) {
		indices.push_back(i);
	}

	while(N>3) {
		ear = find_ear(&vertices[0], N, CCW);
		prev = positive_modulo(ear-1, N);
		next = positive_modulo(ear+1, N);
		result.push_back(indices[prev]);
		result.push_back(indices[ear]);
		result.push_back(indices[next]);
		vertices.erase(vertices.begin()+ear);
		indices.erase(indices.begin()+ear);
		N--;
	}
	result.push_back(indices[0]);
	result.push_back(indices[1]);
	result.push_back(indices[2]);

	return result;
}

std::vector<vec3> triangulate_verts(std::vector<vec3> vertices, int CCW) {
	std::vector<int> indices = triangulate(vertices, CCW);
	std::vector<vec3> result = tris_from_indices(indices, vertices);
	return result;
}

std::vector<vec3> tris_from_indices(std::vector<int> indices, std::vector<vec3> vertices) {
	int N = indices.size();
	std::vector<vec3> result(indices.size());
	for(int i=0; i<N; i++) {
		result.push_back(vertices[indices[i]]);
	}
	return result;
}

