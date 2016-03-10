#include "Circle.h"
using namespace app;

Circle::Circle(Coord p_coord, double p_radius, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Shape2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_CIRCLE;
	m_radius = p_radius;
	m_coordVector.push_back(p_coord);
}


Circle::~Circle()
{
}

bool Circle::checkCollision(Coord p_clickPoint, double p_radius) {
	return calculateDistance(p_clickPoint, m_coordVector[0]) <= (p_radius + m_radius);
}

bool Circle::containedInRect(Coord p_topLeft, double p_width, double p_height) {
	double centerX = p_topLeft.getX() + (p_width / 2);
	double centerY = p_topLeft.getY() + (p_height / 2);

	double distanceX = abs(m_coordVector[0].getX() - centerX);
	double distanceY = abs(m_coordVector[0].getY() - centerY);

	if (distanceX > ((p_width / 2) + m_radius)) return false;
	if (distanceY > ((p_height / 2) + m_radius)) return false;

	if (distanceX <= (p_width / 2)) return true;
	if (distanceY <= (p_height / 2)) return true;

	double distanceCornerToCenter = pow(distanceX - (p_width / 2), 2) + pow(distanceY - (p_height / 2), 2);
	return distanceCornerToCenter <= pow(m_radius, 2);
}

double Circle::getRadius() {
	return m_radius;
}
