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

class Car
{
public:
	float x, y, z;
	float pasX, pasY, pasZ;
	float lungime;
	float latime;
	float inaltime;
	Object3D *car;
	Object3D *roataStgFata;
	Object3D *roataDrFata;
	Object3D *roataStgSpate;
	Object3D *roataDrSpate;
	float razaRoata;
	float unghi;
public:
	Car(void);
	void addObject3D(Visual2D*);
	void perspectiveProject();
	void translate(float, float, float);
	void steerLeft();
	void steerRight();
	void move(int, float, float);
	bool hitsObstacle(float, float, float);
	~Car(void);
};

