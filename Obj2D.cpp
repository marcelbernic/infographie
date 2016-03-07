#include "Obj2D.h"



Obj2D::Obj2D()
{
}

void Obj2D::translate(double p_x, double p_y) {

}

void Obj2D::resize(double p_percent) {

}

void Obj2D::rotate(int p_degree) {

}

bool Obj2D::checkCollision(Coord p_clickPoint, double p_radius) {
	//Line

	//Ellipse

	//Rectangle

	//Triangle
}

double Obj2D::calculateDistance(Coord p_coord1, Coord p_coord2) {
	double x2 = pow((p_coord1.getX() - p_coord2.getX()), 2);
	double y2 = pow((p_coord1.getY() - p_coord2.getY()), 2);
	return sqrt(x2 + y2);
}


Obj2D::~Obj2D()
{
}
