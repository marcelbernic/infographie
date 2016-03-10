#include "Triangle.h"
using namespace app;

Triangle::Triangle(std::vector<Coord> p_coord, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Shape2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_coordVector = p_coord;
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_TRIANGLE;
}


Triangle::~Triangle()
{
}

//TODO
bool Triangle::checkCollision(Coord p_clickPoint, double p_radius) {
	Coord coord1 = m_coordVector[0];
	Coord coord2 = m_coordVector[1];
	Coord coord3 = m_coordVector[2];
	double angle1, angle2, angle3;
	double total;


	//Check if a corner of the triangle is in the circle
	if (calculateDistance(p_clickPoint, coord1) <= p_radius) return true;
	if (calculateDistance(p_clickPoint, coord2) <= p_radius) return true;
	if (calculateDistance(p_clickPoint, coord3) <= p_radius) return true;

	//Check for line/circle collisions
	if (checkCollisionLineCircle(coord1, coord2, p_clickPoint, p_radius)) return true;
	if (checkCollisionLineCircle(coord2, coord3, p_clickPoint, p_radius)) return true;
	if (checkCollisionLineCircle(coord3, coord1, p_clickPoint, p_radius)) return true;

	//Build vectors with each center/corner combination
	double vector1[] {coord1.getX() - p_clickPoint.getX(), coord1.getY() - p_clickPoint.getY()};
	double vector2[] {coord2.getX() - p_clickPoint.getX(), coord2.getY() - p_clickPoint.getY()};
	double vector3[] {coord3.getX() - p_clickPoint.getX(), coord3.getY() - p_clickPoint.getY()};

	//Check if the circle's center is in the triangle
	angle1 = calculateAngle(vector1, vector2);
	//System.out.println("Angle1 180");
	if (angle1 > 180)return false;
	angle2 = calculateAngle(vector2, vector3);
	//System.out.println("Angle2 180");
	if (angle2 > 180)return false;
	angle3 = calculateAngle(vector3, vector1);
	//System.out.println("Angle3 180");
	if (angle3 > 180)return false;

	total = angle1 + angle2 + angle3;

	//System.out.println(angle1);
	//System.out.println(angle2);
	//System.out.println(angle3);
	//System.out.println(total);
	//System.out.println(Math.ceil(total) == 360);
	//System.out.println("Fin\n***************************************\n\n");

	return round(total) == 360;
}

bool Triangle::containedInRect(Coord p_topLeft, double p_width, double p_height) {
	double distanceX = 0;
	double distanceY = 0;
	for (Coord c : m_coordVector) {
		distanceX = c.getX() - p_topLeft.getX();
		distanceY = c.getY() - p_topLeft.getY();
		if (distanceX <= p_width && distanceY <= p_height && distanceX >= 0 && distanceY >= 0) return true;
	}
	return false;
}