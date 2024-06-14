#pragma once
#include "olcPixelGameEngine.h"
#include <vector>
//#include <graphics.h>
#include <iostream>
using namespace std;

using std::vector;

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


void multiplyMatVec(const vec3d& inVec, vec3d& outVec, Mat4x4& mat4x4);
class Shape3D : public olc::PixelGameEngine
{
public:
	Mesh meshCube;
	Mat4x4 projectMat = { 0 };
	float fTheta;

	Shape3D()
	{
		sAppName = "3D Cube";
	}



	bool OnUserCreate() override{
		//initgraph(ScreenWidth(), ScreenHeight(), EX_SHOWCONSOLE);
		fTheta = 0;
		float zNear = 0.10f;
		float zFar = 1000.0f;
		float theta = 90.0f;
		float fTan = 1.0f / tanf(0.5f * theta / 180.0f * 3.1415f);//切换到弧度制
		float aspectRatio = ((float)ScreenHeight() / (float)ScreenWidth());
		projectMat.mat[0][0] = aspectRatio * fTan;
		projectMat.mat[1][1] = fTan;
		projectMat.mat[2][2] = zFar / (zFar - zNear);
		projectMat.mat[2][3] = 1.0f;
		projectMat.mat[3][2] = -zNear * zFar / (zFar - zNear);
		projectMat.mat[3][3] = 0.0f;

		//初始化栅格正方形
		meshCube.tris = {
			{{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f},{1.0f,0.0f,0.0f}},
			{{0.0f,0.0f,0.0f},{1.0f,1.0f,0.0f},{1.0f,0.0f,0.0f}},//SOUTH

			{{0.0f,1.0f,1.0f},{1.0f,0.0f,1.0f},{0.0f,0.0f,1.0f}},
			{{0.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},{1.0f,0.0f,1.0f}},//NORTH

			{{1.0f,1.0f,0.0f},{1.0f,1.0f,1.0f},{1.0f,0.0f,0.0f}},
			{{1.0f,1.0f,1.0f},{1.0f,0.0f,1.0f},{1.0f,0.0f,0.0f}},//EAST

			{{0.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f}},
			{{0.0f,1.0f,1.0f},{0.0f,0.0f,1.0f},{0.0f,0.0f,0.0f}},//WEST

			{{0.0f,1.0f,1.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f}},
			{{0.0f,1.0f,1.0f},{1.0f,1.0f,1.0f},{1.0f,1.0f,0.0f}},//TOP

			{{0.0f,0.0f,1.0f},{1.0f,0.0f,1.0f},{0.0f,0.0f,0.0f}},
			{{0.0f,0.0f,0.0f},{1.0f,0.0f,1.0f},{1.0f,0.0f,0.0f}},//BOTTOM

		};
		return true;
	}
	bool OnUserUpdate(float elapsedTime)override {
		// Erase previous frame
		Clear(olc::DARK_BLUE);
		//cleardevice();
		//BeginBatchDraw();
		fTheta += 1.0f * elapsedTime;

		Mat4x4 matRotZ = { 0 };
		Mat4x4 matRotX = { 0 };//一定要记得初始化

		matRotZ.mat[0][0] = cosf(fTheta);
		matRotZ.mat[0][1] = sinf(fTheta);
		matRotZ.mat[1][0] = -sinf(fTheta);
		matRotZ.mat[1][1] = cosf(fTheta);
		matRotZ.mat[2][2] = 1.0f;
		matRotZ.mat[3][3] = 1.0f;

		matRotX.mat[0][0] = 1.0f;
		matRotX.mat[1][1] = cosf(0.5f * fTheta);
		matRotX.mat[1][2] = sinf(0.5f * fTheta);
		matRotX.mat[2][1] = -sinf(0.5f * fTheta);
		matRotX.mat[2][2] = cosf(0.5f * fTheta);
		matRotX.mat[3][3] = 1.0f;

		for (const auto& tri : meshCube.tris) {

			Triangle triRotatedZ;
			Triangle triRotatedZX;

			multiplyMatVec(tri.p[0], triRotatedZ.p[0], matRotZ);
			multiplyMatVec(tri.p[1], triRotatedZ.p[1], matRotZ);
			multiplyMatVec(tri.p[2], triRotatedZ.p[2], matRotZ);

			multiplyMatVec(triRotatedZ.p[0], triRotatedZX.p[0], matRotX);
			multiplyMatVec(triRotatedZ.p[1], triRotatedZX.p[1], matRotX);
			multiplyMatVec(triRotatedZ.p[2], triRotatedZX.p[2], matRotX);

			Triangle triTranslated;
			triTranslated = triRotatedZX;
			triTranslated.p[0].z = triRotatedZX.p[0].z + 3.0f;
			triTranslated.p[1].z = triRotatedZX.p[1].z + 3.0f;
			triTranslated.p[2].z = triRotatedZX.p[2].z + 3.0f;

			Triangle projectedTri;
			multiplyMatVec(triTranslated.p[0], projectedTri.p[0], projectMat);
			multiplyMatVec(triTranslated.p[1], projectedTri.p[1], projectMat);
			multiplyMatVec(triTranslated.p[2], projectedTri.p[2], projectMat);


			//scale to view

			projectedTri.p[0].x += 1.0f;		projectedTri.p[0].y += 1.0f;
			projectedTri.p[1].x += 1.0f;		projectedTri.p[1].y += 1.0f;
			projectedTri.p[2].x += 1.0f;		projectedTri.p[2].y += 1.0f;


			projectedTri.p[0].x *= 0.5f * (float)ScreenWidth();
			projectedTri.p[0].y *= 0.5f * (float)ScreenHeight();
			projectedTri.p[1].x *= 0.5f * (float)ScreenWidth();
			projectedTri.p[1].y *= 0.5f * (float)ScreenHeight();
			projectedTri.p[2].x *= 0.5f * (float)ScreenWidth();
			projectedTri.p[2].y *= 0.5f * (float)ScreenHeight();


			/*
			line(projectedTri.p[0].x, projectedTri.p[0].y, projectedTri.p[1].x, projectedTri.p[1].y);
			
			line(projectedTri.p[1].x, projectedTri.p[1].y, projectedTri.p[2].x, projectedTri.p[2].y);
		
			line(projectedTri.p[2].x, projectedTri.p[2].y, projectedTri.p[0].x, projectedTri.p[0].y);
			*/

			DrawLine(projectedTri.p[0].x, projectedTri.p[0].y, projectedTri.p[1].x, projectedTri.p[1].y, olc::YELLOW);
			DrawLine(projectedTri.p[1].x, projectedTri.p[1].y, projectedTri.p[2].x, projectedTri.p[2].y, olc::YELLOW);
			DrawLine(projectedTri.p[2].x, projectedTri.p[2].y, projectedTri.p[0].x, projectedTri.p[0].y, olc::YELLOW);
			
		}
		
		//EndBatchDraw();
		return true;
	}

};