#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include <iostream>
#include <windows.h>
#define PI 3.14159265358979323846
#pragma once
class Obstacle
{
public:
	float x, y, z;
	float laturaPiramida;
	float pasX, pasY, pasZ;
	Object3D *obstacle;
	float centerX;
	float scale;
	float inaltime;
	float distance;
	float zMasina;
public:
	Obstacle(int, int, int, int, float);
	void addObject3D(Visual2D*);
	void perspectiveProject();
	void translate(float, float, float);
	void move(int);
	~Obstacle(void);
};

