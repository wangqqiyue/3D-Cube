#pragma once
#include <vector>
#include <iostream>

using std::vector;
using namespace std;

class vec3d {
public:
	float x;
	float y;
	float z;
	vec3d() = default;
	vec3d(float x,float y,float z):x(x),y(y),z(z){}
};

class Triangle {
public:
	vec3d p[3];
	Triangle() = default;
	Triangle(vec3d p0,vec3d p1,vec3d p2);
	void draw();
};


class Mesh {
public:
	vector<Triangle> tris;
};

struct Mat4x4 {
	float mat[4][4];
};

class Shape3D{
public:
	Mesh meshCube;
	Mat4x4 projectMat={0};
	float fTheta;

	Shape3D();
	void draw(float elapsedTime);
};

class Screen {
public:
	static float width;
	static float height;
};
