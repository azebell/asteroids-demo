
#include "quat.h"
#include <math.h>

quat4 quat4AxisAngle(vec3 axis, float theta) {
	quat4 result;
	axis = vec3Unit(axis);
	
	float tmp = sin(theta/2.0);
	result.v.x = axis.x*tmp;
	result.v.y = axis.y*tmp;
	result.v.z = axis.z*tmp;
	result.w = cos(theta/2.0);

	return quat4Unit(result);
}

float quat4Norm(quat4 Q) {
	return sqrt(Q.w*Q.w + Q.v.x*Q.v.x + Q.v.y*Q.v.y + Q.v.z*Q.v.z);
}

quat4 quat4Unit(quat4 Q) {
	float norm = quat4Norm(Q);
	return quat4Scale(1/norm, Q);
}

quat4 quat4Scale(float s, quat4 Q) {
	Q.w *= s;
	Q.v.x *= s;
	Q.v.y *= s;
	Q.v.z *= s;
	return Q;
}

quat4 quat4Sum(quat4 A, quat4 B) {
	quat4 Q = A;
	Q.w += B.w;
	Q.v.x += B.v.x;
	Q.v.y += B.v.y;
	Q.v.z += B.v.z;
	return Q;
}

quat4 quat4Diff(quat4 A, quat4 B) {
	quat4 Q = A;
	Q.w -= B.w;
	Q.v.x -= B.v.x;
	Q.v.y -= B.v.y;
	Q.v.z -= B.v.z;
	return Q;
}

quat4 quat4Mult(quat4 A, quat4 B) {
	quat4 Q;
	Q.w = A.w*B.w + vec3Dot(A.v, B.v);
	Q.v = vec3Cross(A.v, B.v);
	Q.v = vec3Sum(A.v, vec3Scale(B.v, A.w));
	Q.v = vec3Sum(A.v, vec3Scale(A.v, B.w));
	return Q;
}

quat4 operator *(float A, quat4 B) {return quat4Scale(A,B);}
quat4 operator +(quat4 A, quat4 B) {return quat4Sum(A,B);}
quat4 operator -(quat4 A, quat4 B) {return quat4Diff(A,B);}
quat4 operator *(quat4 A, quat4 B) {return quat4Mult(A,B);}

