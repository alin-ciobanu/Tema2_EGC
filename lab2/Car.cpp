#include "Car.h"


Car::Car(void)
{

	x = 350;
	y = 0;
	z = 140;

	unghi = 0;
	pasX = pasY = pasZ = 0;

	latime = 80;
	inaltime = 50;
	lungime = 250;

	razaRoata = 20;

	//se deseneaza masina
	vector <Point3D*> vertices;
	vector <Face*> faces;

	//varfurile de jos
	vertices.push_back(new Point3D(x,y,z));
	vertices.push_back(new Point3D(x + latime,y,z));
	vertices.push_back(new Point3D(x + latime,y,z + lungime));
	vertices.push_back(new Point3D(x,y,z + lungime));
	//varfurile de sus
	vertices.push_back(new Point3D(x,y + inaltime,z));
	vertices.push_back(new Point3D(x + latime,y + inaltime,z));
	vertices.push_back(new Point3D(x + latime,y + inaltime,z + lungime));
	vertices.push_back(new Point3D(x,y + inaltime,z + lungime));

	
	//cele 6 fete
	vector <int> contour;
	//fata jos
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(3);
	faces.push_back(new Face(contour));
	//fata sus
	contour.clear();
	contour.push_back(4);
	contour.push_back(5);
	contour.push_back(6);
	contour.push_back(7);
	faces.push_back(new Face(contour));
	//fata fata
	contour.clear();
	contour.push_back(0);
	contour.push_back(1);
	contour.push_back(5);
	contour.push_back(4);
	faces.push_back(new Face(contour));
	//fata dreapta
	contour.clear();
	contour.push_back(1);
	contour.push_back(2);
	contour.push_back(6);
	contour.push_back(5);
	faces.push_back(new Face(contour));
	//fata spate
	contour.clear();
	contour.push_back(2);
	contour.push_back(3);
	contour.push_back(7);
	contour.push_back(6);
	faces.push_back(new Face(contour));
	//fata stanga
	contour.clear();
	contour.push_back(3);
	contour.push_back(0);
	contour.push_back(4);
	contour.push_back(7);
	faces.push_back(new Face(contour));

	car = new Object3D(vertices,faces,Color(1,0,0),false);

	// varfurile rotii stanga spate
	vertices.clear();
	float centruRoataY, centruRoataZ;
	centruRoataY = y;
	centruRoataZ = z + 40;
	contour.clear();
	faces.clear();
	for (float u = 0; u < 2 * PI; u = u + PI/360) {
		float yy = centruRoataY + razaRoata * sin(u);
		float zz = centruRoataZ + razaRoata * cos(u);
		vertices.push_back(new Point3D(x - 1, yy, zz));
		vertices.push_back(new Point3D(x - 15, yy, zz));
		if (vertices.size() > 3) {
			for (int k = vertices.size() - 4; k < vertices.size(); k++) {
				contour.push_back(k);
			}
			faces.push_back(new Face(contour));
			contour.clear();
		}
	}

	roataStgSpate = new Object3D(vertices, faces, Color(0,1,0), true);

	// varfurile rotii stanga spate
	vertices.clear();
	centruRoataY = y;
	centruRoataZ = z + 200;
	contour.clear();
	faces.clear();
	for (float u = 0; u < 2 * PI; u = u + PI/360) {
		float yy = centruRoataY + razaRoata * sin(u);
		float zz = centruRoataZ + razaRoata * cos(u);
		vertices.push_back(new Point3D(x - 1, yy, zz));
		vertices.push_back(new Point3D(x - 15, yy, zz));
		if (vertices.size() > 3) {
			for (int k = vertices.size() - 4; k < vertices.size(); k++) {
				contour.push_back(k);
			}
			faces.push_back(new Face(contour));
			contour.clear();
		}
	}

	roataStgFata = new Object3D(vertices, faces, Color(0,1,0), true);
	
	// varfurile rotii dreapta spate
	vertices.clear();
	centruRoataY = y;
	centruRoataZ = z + 40;
	contour.clear();
	faces.clear();
	for (float u = 0; u < 2 * PI; u = u + PI/360) {
		float yy = centruRoataY + razaRoata * sin(u);
		float zz = centruRoataZ + razaRoata * cos(u);
		vertices.push_back(new Point3D(x + latime + 1, yy, zz));
		vertices.push_back(new Point3D(x + latime + 15, yy, zz));
		if (vertices.size() > 3) {
			for (int k = vertices.size() - 4; k < vertices.size(); k++) {
				contour.push_back(k);
			}
			faces.push_back(new Face(contour));
			contour.clear();
		}
	}

	roataDrSpate = new Object3D(vertices, faces, Color(0,1,0), true);

	// varfurile rotii dreapta fata
	vertices.clear();
	centruRoataY = y;
	centruRoataZ = z + 200;
	contour.clear();
	faces.clear();
	for (float u = 0; u < 2 * PI; u = u + PI/360) {
		float yy = centruRoataY + razaRoata * sin(u);
		float zz = centruRoataZ + razaRoata * cos(u);
		vertices.push_back(new Point3D(x + latime + 1, yy, zz));
		vertices.push_back(new Point3D(x + latime + 15, yy, zz));
		if (vertices.size() > 3) {
			for (int k = vertices.size() - 4; k < vertices.size(); k++) {
				contour.push_back(k);
			}
			faces.push_back(new Face(contour));
			contour.clear();
		}
	}

	roataDrFata = new Object3D(vertices, faces, Color(0,1,0), true);

}

void Car::addObject3D(Visual2D* playfield) {

	DrawingWindow::addObject3D_to_Visual2D(car, playfield);
	DrawingWindow::addObject3D_to_Visual2D(roataStgSpate, playfield);
	DrawingWindow::addObject3D_to_Visual2D(roataDrSpate, playfield);
	DrawingWindow::addObject3D_to_Visual2D(roataDrFata, playfield);
	DrawingWindow::addObject3D_to_Visual2D(roataStgFata, playfield);

}

void Car::perspectiveProject() {

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();

	Transform3D::translateMatrix(-(x + latime / 2), -(y + inaltime / 2), -(z + lungime / 2));
	Transform3D::rotateMatrixOy(unghi);
	Transform3D::translateMatrix((x + latime / 2), (y + inaltime / 2), (z + lungime / 2));

	Transform3D::translateMatrix(pasX, pasY, pasZ);

	Transform3D::perspectiveProjectionMatrix(x - pasX + latime/2, y + inaltime + 2000, -(z + lungime + 5000));
	Transform3D::applyTransform(car);
	Transform3D::applyTransform(roataStgSpate);
	Transform3D::applyTransform(roataDrSpate);
	Transform3D::applyTransform(roataDrFata);
	Transform3D::applyTransform(roataStgFata);

}

void Car::translate(float x, float y, float z) {

	pasX += x;
	pasY += y;
	pasZ += z;

}

void Car::steerLeft() {

	if (unghi > PI / 4)
		return;

	else
		unghi += PI / 180;

}

void Car::steerRight() {

	if (unghi < - PI / 4)
		return;
	else
		unghi -= PI / 180;

}

void Car::move(int speed, float x, float width)
{

	while (speed--)
	{
		pasX -= sin(unghi);

		if ((this->x + latime + pasX) < x + 50 || (this->x + pasX) > (x + width - 50)) {
			pasX += sin(unghi);
		}
	}

}

bool Car::hitsObstacle(float xObstSt, float xObstDr, float zObst)
{

	if (zObst - z - pasZ < 11 && zObst - z - pasZ > -1)
	{

		if ((xObstSt >= (x + pasX) && xObstSt <= (x + pasX + latime))
			|| (xObstDr >= (x + pasX) && xObstDr <= (x + pasX + latime))
			)
		{
			return true;
		}
	}

	return false;

}


Car::~Car(void)
{
}
