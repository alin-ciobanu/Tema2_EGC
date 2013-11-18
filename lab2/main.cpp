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
int heightScoreBoard = 40;

Car *car;
Obstacle *obstacle;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{

	FreeConsole(); // ascunde consola

	v2d_playfield = new Visual2D
		(0 + margini, 0 + margini, 
		DrawingWindow::width - margini, DrawingWindow::height - margini - heightScoreBoard, 
		0 + margini, 0 + margini + heightScoreBoard,
		DrawingWindow::width - margini, DrawingWindow::height - margini);
	v2d_playfield->cadruFereastra(Color(0, 1, 1));
	addVisual2D(v2d_playfield);

	car = new Car();
	obstacle = new Obstacle(1);

	car->addObject3D(v2d_playfield);
	obstacle->addObject3D(v2d_playfield);

}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	car->perspectiveProject();
	obstacle->perspectiveProject();

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
		case 27 : exit(0);
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