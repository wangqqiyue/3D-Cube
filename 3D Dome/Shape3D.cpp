#include "Shape3D.h"
#include <math.h>

Triangle::Triangle(vec3d p0, vec3d p1, vec3d p2){
	p[0] = p0;
	p[1] = p1;
	p[2] = p2;
}

void multiplyMatVec(const vec3d& inVec, vec3d& outVec, Mat4x4& mat4x4) {
	float x, y, z, w;
	x = inVec.x;
	y = inVec.y;
	z = inVec.z;

	outVec.x = x * mat4x4.mat[0][0] + y * mat4x4.mat[1][0] + z * mat4x4.mat[2][0] + mat4x4.mat[3][0];
	outVec.y = x * mat4x4.mat[0][1] + y * mat4x4.mat[1][1] + z * mat4x4.mat[2][1] + mat4x4.mat[3][1];
	outVec.z = x * mat4x4.mat[0][2] + y * mat4x4.mat[1][2] + z * mat4x4.mat[2][2] + mat4x4.mat[3][2];
	w = x * mat4x4.mat[0][3] + y * mat4x4.mat[1][3] + z * mat4x4.mat[2][3] + mat4x4.mat[3][3];
	if (0.0f != w) {
		outVec.x /= w;
		outVec.y /= w;
		outVec.z /= w;
	}

	return;
}
