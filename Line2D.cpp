#include "Line2D.h"
using namespace app;

Line2D::Line2D(std::vector<Coord> p_coord, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Shape2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_coordVector = p_coord;
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_LINE;
}


Line2D::~Line2D()
{
}

//TODO
bool Line2D::checkCollision(Coord p_clickPoint, double p_radius) {
	return checkCollisionLineCircle(m_coordVector[0], m_coordVector[1], p_clickPoint, p_radius);
}

bool Line2D::containedInRect(Coord p_topLeft, double p_width, double p_height) {
	double distanceX = 0;
	double distanceY = 0;
	for (Coord c : m_coordVector) {
		distanceX = c.getX() - p_topLeft.getX();
		distanceY = c.getY() - p_topLeft.getY();
		if (distanceX <= p_width && distanceY <= p_height && distanceX >= 0 && distanceY >= 0) return true;
	}
	return false;
}