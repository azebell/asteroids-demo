#ifndef STRUCTS
#define STRUCTS

typedef struct vector3D		//stores data for a 3D vector used for calcualtions
{
	float x;
	float y;
	float z;

	vector3D()
	{}

	vector3D(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
} vector3D;

#endif
