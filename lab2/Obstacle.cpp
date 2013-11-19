#include "Obstacle.h"


Obstacle::Obstacle(int x, int y, int z, int i, float zMasina)
{

	this->x = x;
	this->y = y;
	this->z = z;

	pasX = pasY = pasZ = 0;
	centerX = 350;

	this->zMasina = zMasina;
	distance = abs(zMasina - (z + pasZ));

	laturaPiramida = 100;

	if (i == 0) {

		//se deseneaza piramida
		vector <Point3D*> vertices;
		vector <Face*> faces;

		//varfurile de jos
		vertices.push_back(new Point3D(x,y,z));
		vertices.push_back(new Point3D(x + laturaPiramida,y,z));
		vertices.push_back(new Point3D(x + laturaPiramida / 2, y, z + (sqrt(3)/2)*laturaPiramida));
		//varful de sus
		inaltime = laturaPiramida;
		vertices.push_back(new Point3D(x + laturaPiramida / 2, y + inaltime, z + (sqrt(3)/6)*laturaPiramida));

		//cele 6 fete
		vector <int> contour;
		//fata jos
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		faces.push_back(new Face(contour));
		//fata 1
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(3);
		faces.push_back(new Face(contour));
		//fata 2
		contour.clear();
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));
		//fata 3
		contour.clear();
		contour.push_back(0);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));

		obstacle = new Object3D(vertices,faces,Color(1,0,0),false);

	}

	if (i == 1) {

		//se deseneaza piramida
		vector <Point3D*> vertices;
		vector <Face*> faces;

		//varfurile de jos
		vertices.push_back(new Point3D(x,y,z));
		vertices.push_back(new Point3D(x + laturaPiramida,y,z));
		vertices.push_back(new Point3D(x + laturaPiramida,y,z + laturaPiramida));
		vertices.push_back(new Point3D(x,y,z + laturaPiramida));
		//varful de sus
		inaltime = laturaPiramida;
		vertices.push_back(new Point3D(x + laturaPiramida / 2, y + inaltime, z + laturaPiramida / 2));

		//cele 6 fete
		vector <int> contour;
		//fata jos
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(3);
		faces.push_back(new Face(contour));
		//fata 1
		contour.clear();
		contour.push_back(0);
		contour.push_back(1);
		contour.push_back(4);
		faces.push_back(new Face(contour));
		//fata 2
		contour.clear();
		contour.push_back(1);
		contour.push_back(2);
		contour.push_back(4);
		faces.push_back(new Face(contour));
		//fata 3
		contour.clear();
		contour.push_back(2);
		contour.push_back(3);
		contour.push_back(4);
		faces.push_back(new Face(contour));
		//fata 4
		contour.clear();
		contour.push_back(0);
		contour.push_back(3);
		contour.push_back(4);
		faces.push_back(new Face(contour));

		obstacle = new Object3D(vertices,faces,Color(1,0,0),false);

	}

}

void Obstacle::addObject3D(Visual2D* playfield) {

	DrawingWindow::addObject3D_to_Visual2D(obstacle, playfield);

}

void Obstacle::perspectiveProject() {

	Transform3D::loadIdentityModelMatrix();
	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::translateMatrix(-(x + laturaPiramida / 2), - (y + inaltime / 2), -(z + (sqrt(3)/4) * laturaPiramida));
	if (distance > 700)
		scale = 700 / distance;
	else
		scale = 1;
	Transform3D::scaleMatrix(scale, scale, scale);
	Transform3D::translateMatrix((x + laturaPiramida / 2), (y + inaltime / 2), z + (sqrt(3)/4) * laturaPiramida);
	Transform3D::translateMatrix(pasX, pasY, pasZ);

	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::perspectiveProjectionMatrix(centerX + laturaPiramida / 2, y + laturaPiramida + 2000, -(z + laturaPiramida + 5000));
	Transform3D::applyTransform(obstacle);

}

void Obstacle::translate(float x, float y, float z) {

	pasX += x;
	pasY += y;
	pasZ += z;

}

void Obstacle::move (int speed) {

	if (z + pasZ < - 4 * laturaPiramida)
		return;

	while (speed--)
	{

		distance = abs(zMasina - (z + pasZ));
		pasZ--;

	}

}


Obstacle::~Obstacle(void)
{
}
