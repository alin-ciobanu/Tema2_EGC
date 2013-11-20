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
Visual2D *v2d_scoreboard;
float margini = 30;
float heightScoreBoard = 40;

int i = 0;

float width_playfield, height_playfield;

float zMAX = 3900;
float xSt, xMijl, xDr;
int frameNo = 0;

int speed;
int speedMAX = 50;
int oprire_inertie = 0;

int score = 0;
Color colorText = Color(18.0f/255.0f, 105.0f/255.0f, 99.0f/255.0f);

Car *car;
vector<Obstacle*> obstacles;

bool keyDownIsPressed;
bool keyUpIsPressed;
bool keyRightIsPressed;
bool keyLeftIsPressed;

int n = 0;

Text *textScore, *textSpeed;

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{

	FreeConsole(); // ascunde consola

	speed = 0;

	xSt = 130;
	xMijl = 350;
	xDr = 550;

	width_playfield = DrawingWindow::width - 2 * margini;
	height_playfield = DrawingWindow::height - 2 * margini - heightScoreBoard;
	v2d_playfield = new Visual2D
		(0 + margini, 0 + margini, 
		DrawingWindow::width - margini, DrawingWindow::height - margini - heightScoreBoard, 
		0 + margini, 0 + margini + heightScoreBoard,
		DrawingWindow::width - margini, DrawingWindow::height - margini);
	v2d_playfield->cadruFereastra(Color(0, 1, 1));
	addVisual2D(v2d_playfield);

	v2d_scoreboard = new Visual2D
		(0 + margini, 0 + DrawingWindow::height - margini - heightScoreBoard,
		DrawingWindow::width - margini, DrawingWindow::height - margini, 
		0 + margini, 0 + margini, 
		DrawingWindow::width - margini, 0 + margini + heightScoreBoard);
	addVisual2D(v2d_scoreboard);

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

	Text* text1 = new Text("Score: ", Point2D(50, 660), colorText, GLUT_BITMAP_9_BY_15);
	addText_to_Visual2D(text1, v2d_scoreboard);

	string scoreT = to_string(score);
	textScore = new Text(scoreT, Point2D(160, 660), colorText, GLUT_BITMAP_9_BY_15);
	addText_to_Visual2D(textScore, v2d_scoreboard);

	Text* text2 = new Text("Speed: ", Point2D(200, 660), colorText, GLUT_BITMAP_9_BY_15);
	addText_to_Visual2D(text2, v2d_scoreboard);

	string speedT = to_string(speed);
	textSpeed = new Text(speedT, Point2D(260, 660), colorText, GLUT_BITMAP_9_BY_15);
	addText_to_Visual2D(textSpeed, v2d_scoreboard);

	car = new Car();
	car->addObject3D(v2d_playfield);

}


//functia care permite animatia
void DrawingWindow::onIdle()
{

	for (int i = 0; i < obstacles.size(); i++)
	{
		if (car->hitsObstacle(obstacles[i]->x + obstacles[i]->pasX, 
				obstacles[i]->x + obstacles[i]->pasX + obstacles[i]->laturaPiramida,
				obstacles[i]->z + obstacles[i]->pasZ
				))
			{

				Text* lose;
				lose = new Text("Game over.", Point2D(350, 660), colorText, GLUT_BITMAP_9_BY_15);
				addText_to_Visual2D(lose, v2d_scoreboard);

				return;

			}
	}

	if (speed > 5)
	{
		score++;
	}
	if (speed < speedMAX && speed > 5)
	{
		score += 5;
	}

	removeText_from_Visual2D(textScore, v2d_scoreboard);
	string scoreT = to_string(score);
	textScore = new Text(scoreT, Point2D(120, 660), colorText, GLUT_BITMAP_9_BY_15);
	addText_to_Visual2D(textScore, v2d_scoreboard);

	removeText_from_Visual2D(textSpeed, v2d_scoreboard);
	string speedT = to_string(speed);
	textSpeed = new Text(speedT, Point2D(260, 660), colorText, GLUT_BITMAP_9_BY_15);
	addText_to_Visual2D(textSpeed, v2d_scoreboard);

	if (frameNo > speed + 10)
	{
		float obstX = xSt;
		float carX = car->x + car->pasX;

		if (carX < xSt)
			obstX = xSt;
		else if (carX >= xSt && carX < xMijl)
			obstX = xMijl;
		else
			obstX = xDr;

		int type = (int) (ceil(carX)) % 3;

		Obstacle *obst = new Obstacle(obstX, 0, zMAX, type, car->z + car->pasZ, v2d_playfield);
		obstacles.push_back(obst);
		n++;
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
		speed ++;
		if (speed > speedMAX)
			speed = speedMAX;
	}
	if (keyDownIsPressed)
	{
		speed -= 2;
		if (speed < 0)
			speed = 0;
	}

	if (!keyDownIsPressed && !keyUpIsPressed)
	{
		if (oprire_inertie > 10)
		{
			oprire_inertie = 0;
			speed--;
		}
		else
		{
			oprire_inertie++;
		}
		if (speed < 0)
			speed = 0;
	}

	car->move(speed, margini, width_playfield);
	car->perspectiveProject();

	for (int i = 0; i < n; i++)
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