#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Transform3D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "car.h"
#include "obstacle.h"
#include <iostream>
#include <windows.h>


#define PI 3.14159265358979323846
#define inf 1000000
using namespace std;

Visual2D *v2d_playfield;
float margini = 30;
float heightScoreBoard = 40;

float zMAX = 3900;
float xSt, xMijl, xDr;
int frameNo = 0;

int speed;
int speedMAX = 50;

Car *car;
vector<Obstacle*> obstacles;

bool keyDownIsPressed;
bool keyUpIsPressed;
bool keyRightIsPressed;
bool keyLeftIsPressed;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{

	FreeConsole(); // ascunde consola

	speed = 0;

	xSt = 130;
	xMijl = 350;
	xDr = 550;

	float width_playfield, height_playfield;
	width_playfield = DrawingWindow::width - 2 * margini;
	height_playfield = DrawingWindow::height - 2 * margini - heightScoreBoard;
	v2d_playfield = new Visual2D
		(0 + margini, 0 + margini, 
		DrawingWindow::width - margini, DrawingWindow::height - margini - heightScoreBoard, 
		0 + margini, 0 + margini + heightScoreBoard,
		DrawingWindow::width - margini, DrawingWindow::height - margini);
	v2d_playfield->cadruFereastra(Color(0, 1, 1));
	addVisual2D(v2d_playfield);

	Line2D *linieStg, *linieStgMijloc, *linieDrMijloc, *linieDr;
	float borderSoseaSus = width_playfield / 5;
	float ox, oy;
	ox = margini;
	oy = margini;
	linieStg = new Line2D(Point2D(ox + width_playfield / 5, oy + height_playfield), Point2D(ox, oy), 
		Color(84.0f/255.0f, 84.0f/255.0f,84.0f/255.0f));
	linieStgMijloc = new Line2D(Point2D(ox + 2 * width_playfield / 5, oy + height_playfield), Point2D(ox + width_playfield / 3, oy), 
		Color(84.0f/255.0f, 84.0f/255.0f,84.0f/255.0f));
	linieDrMijloc = new Line2D(Point2D(ox + 3 * width_playfield / 5, oy + height_playfield), Point2D(ox + 2 * width_playfield / 3, oy), 
		Color(84.0f/255.0f, 84.0f/255.0f,84.0f/255.0f));
	linieDr = new Line2D(Point2D(ox + 4 * width_playfield / 5, oy + height_playfield), Point2D(ox + width_playfield, oy), 
		Color(84.0f/255.0f, 84.0f/255.0f,84.0f/255.0f));

	addObject2D_to_Visual2D(linieDr, v2d_playfield);
	addObject2D_to_Visual2D(linieDrMijloc, v2d_playfield);
	addObject2D_to_Visual2D(linieStgMijloc, v2d_playfield);
	addObject2D_to_Visual2D(linieStg, v2d_playfield);

	car = new Car();
	obstacles.push_back(new Obstacle(xMijl, 0, zMAX, 1, car->z + car->pasZ));

	car->addObject3D(v2d_playfield);
	obstacles[0]->addObject3D(v2d_playfield);

}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	if (frameNo > speed && speed != 0)
	{
		float obstX;
		if ((car->x + car->pasX) < xSt)
			obstX = xSt;
		else if ((car->x + car->pasX) > xSt && (car->x + car->pasX) < xMijl)
			obstX = xMijl;
		else
			obstX = xDr;

		int type = (int) (ceil(car->x + car->pasX)) % 2;

		obstacles.push_back(new Obstacle(obstX, 0, zMAX, type, car->z + car->pasZ));
		obstacles[obstacles.size() - 1]->addObject3D(v2d_playfield);
		frameNo = 0;
	}
	else
	{
		frameNo++;
	}

	if (keyLeftIsPressed) 
	{
		car->steerLeft();
	}

	if (keyRightIsPressed) 
	{
		car->steerRight();
	}

	if (keyUpIsPressed)
	{
		speed += 1;
		if (speed > speedMAX)
			speed = speedMAX;
	}
	if (keyDownIsPressed)
	{
		speed -= 2;
		if (speed < 0)
			speed = 0;
	}

	car->move(speed);
	car->perspectiveProject();

	for (int i = 0; i < obstacles.size(); i++)
	{
		obstacles[i]->move(speed);
		obstacles[i]->perspectiveProject();
	}

}

//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{

		case 27: exit(0);

		case GLUT_KEY_LEFT: {
			keyLeftIsPressed = true;
			break;
							}

		case GLUT_KEY_RIGHT: {
			keyRightIsPressed = true;
			break;
							 }

		case GLUT_KEY_UP: {
			keyUpIsPressed = true;
			break;
						  }
		case GLUT_KEY_DOWN: {
			keyDownIsPressed = true;
			break;
							}
	}
}

//functia care defineste ce se intampla cand la ridicarea unei taste
void DrawingWindow::upKey(unsigned char key)
{

	switch(key)
	{

		case GLUT_KEY_LEFT: {
			keyLeftIsPressed = false;
			break;
							}

		case GLUT_KEY_RIGHT: {
			keyRightIsPressed = false;
			break;
							 }

		case GLUT_KEY_UP: {
			keyUpIsPressed = false;
			break;
						  }
		case GLUT_KEY_DOWN: {
			keyDownIsPressed = false;
			break;
							}
	}

}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
}


int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 800, 700, 200, 10, "Crazy Driver");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}