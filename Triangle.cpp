#include "Triangle.h"



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
	return false;
}