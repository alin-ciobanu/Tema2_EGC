#include "Obstacle.h"


Obstacle::Obstacle(int i)
{

	x = 100;
	y = 0;
	z = 1000;

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
		float inaltime = laturaPiramida;
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
		float inaltime = laturaPiramida;
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

	Transform3D::loadIdentityProjectionMatrix();
	Transform3D::perspectiveProjectionMatrix(x + laturaPiramida + 200, y + laturaPiramida + 2000, -(z + laturaPiramida + 5000));
	Transform3D::applyTransform(obstacle);

}

void Obstacle::translate(float x, float y, float z) {
	
	Transform3D::loadIdentityModelMatrix();
	Transform3D::translateMatrix(x, y, z);
	Transform3D::applyTransform(obstacle);

}


Obstacle::~Obstacle(void)
{
}
