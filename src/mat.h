
/// 4x4 Matrix struct, identity matrix, and matrix from array

#ifndef MAT_H
#define MAT_H

//#include "vec.h"
#include "includes.h"
#include "structs.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct mat4 {
	float e[16];
} mat4;

// needs to be a size 16 array
mat4 mat4FromArray(float *ma);

mat4 mmm(mat4 A, mat4 B);

mat4 mat4Identity();

#ifdef __cplusplus
}

mat4 operator *(mat4 T1, mat4 T2);

#endif // __cplusplus

#endif // MAT_H

