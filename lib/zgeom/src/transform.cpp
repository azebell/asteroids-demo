
#include "transform.h"
#include <math.h>


void mat4Translate(mat4 *m, vec3 translate) {
	m->e[3]  += translate.x;
	m->e[7]  += translate.y;
	m->e[11] += translate.z;
}

void mat4Scale(mat4 *m, vec3 scale) {
	mat4 t = mat4Identity();
	t.e[0]  *= scale.x;
	t.e[5]  *= scale.y;
	t.e[10] *= scale.z;
	*m = mmm(t, *m);
}

void mat4RotateX(mat4 *m, float theta) {
	mat4 t = mat4Identity();
	t.e[5]  = cos(theta);
	t.e[6]  = -sin(theta);
	t.e[9]  = sin(theta);
	t.e[10] = cos(theta);
	*m = mmm(t, *m);
}

void mat4RotateY(mat4 *m, float theta) {
	mat4 t = mat4Identity();
	t.e[0]  = cos(theta);
	t.e[2]  = sin(theta);
	t.e[8]  = -sin(theta);
	t.e[10] = cos(theta);
	*m = mmm(t, *m);
}

void mat4RotateZ(mat4 *m, float theta) {
	mat4 t = mat4Identity();
	t.e[0] = cos(theta);
	t.e[1] = -sin(theta);
	t.e[4] = sin(theta);
	t.e[5] = cos(theta);
	*m = mmm(t, *m);
}

void mat4Rotate(mat4 *m, vec3 axis, float theta) {
	// https://en.wikipedia.org/wiki/Rotation_matrix
	mat4 t = mat4Identity();
	vec3 u = vec3Unit(axis);
	float ct = cos(theta);
	float st = sin(theta);

	t.e[0]  = ct + u.x*u.x*(1-ct);
	t.e[1]  = u.x*u.y*(1-ct) - u.z*st;
	t.e[2]  = u.x*u.z*(1-ct) + u.y*st;

	t.e[4]  = u.x*u.y*(1-ct) + u.z*st;
	t.e[5]  = ct - u.y*u.y*(1-ct);
	t.e[6]  = u.y*u.z*(1-ct) + u.x*st;

	t.e[8]  = u.x*u.z*(1-ct) + u.y*st;
	t.e[9]  = u.y*u.z*(1-ct) + u.x*st;
	t.e[10] = ct - u.z*u.z*(1-ct);

	*m = mmm(t, *m);
}

mat4 mat4LookAt(vec3 target, vec3 pos, vec3 up) {
	mat4 t = mat4Identity();

	vec3 zaxis = vec3Unit(vec3Diff(target, pos));
	vec3 xaxis = vec3Unit(vec3Cross(up, zaxis));
	vec3 yaxis = vec3Cross(zaxis, xaxis);

	t.e[0]  = xaxis.x;
	t.e[1]  = yaxis.x;
	t.e[2]  = zaxis.x;

	t.e[4]  = xaxis.y;
	t.e[5]  = yaxis.y;
	t.e[6]  = zaxis.y;

	t.e[8]  = xaxis.z;
	t.e[9]  = yaxis.z;
	t.e[10]  = zaxis.z;

	t.e[12] = -vec3Dot(xaxis, pos);
	t.e[13] = -vec3Dot(yaxis, pos);
	t.e[14] = -vec3Dot(zaxis, pos);

	return t;
}

mat4 quat4ToMat4(quat4 Q) {
	Q = quat4Unit(Q);
	mat4 t = mat4Identity();

	t.e[0]  = 1 - 2*(Q.v.y*Q.v.y + Q.v.z*Q.v.z);
	t.e[1]  = 2*(Q.v.x*Q.v.y - Q.v.z*Q.w);
	t.e[2]  = 2*(Q.v.x*Q.v.z + Q.v.y*Q.w);

	t.e[4]  = 2*(Q.v.x*Q.v.y + Q.v.z*Q.w);
	t.e[5]  = 1 - 2*(Q.v.x*Q.v.x + Q.v.z*Q.v.z);
	t.e[6]  = 2*(Q.v.y*Q.v.z - Q.v.x*Q.w);

	t.e[8]  = 2*(Q.v.x*Q.v.z - Q.v.y*Q.w);
	t.e[9]  = 2*(Q.v.y*Q.v.z + Q.v.x*Q.w);
	t.e[10] = 1 - 2*(Q.v.x*Q.v.x + Q.v.y*Q.v.y);

	return t;
}

void applyTransform(mat4 T, vec3 *p, vec3 *pT, int N) {
	vec3 v;
	for(int i=0; i<N; i++) {
		v = p[i];
		pT[i].x = v.x*T.e[0] + v.y*T.e[1] + v.z*T.e[2]  + T.e[3];
		pT[i].y = v.x*T.e[4] + v.y*T.e[5] + v.z*T.e[6]  + T.e[7];
		pT[i].z = v.x*T.e[8] + v.y*T.e[9] + v.z*T.e[10] + T.e[11];
	}
}

std::vector<vec3> applyTransform(mat4 T, std::vector<vec3> p) {
	std::vector<vec3> pT(p.size());
	applyTransform(T, &p[0], &pT[0], p.size());
	return pT;
}

std::vector<vec3> operator *(mat4 T, std::vector<vec3> p) {
	return applyTransform(T, p);
}

mat4 operator *(quat4 Q, mat4 T) {
	mat4 qT = quat4ToMat4(Q);
	return mmm(qT, T);
}

mat4 operator *(mat4 T, quat4 Q) {
	mat4 qT = quat4ToMat4(Q);
	return mmm(T, qT);
}

