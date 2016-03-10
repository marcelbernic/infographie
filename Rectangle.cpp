#include "Rectangle.h"
using namespace app;

Rectangle::Rectangle(Coord p_coord, double p_width, double p_height, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Shape2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_width = p_width;
	m_height = p_height;
	m_coordVector = std::vector<Coord>();
	m_coordVector.push_back(p_coord);
	m_coordVector.push_back(Coord(p_coord.getX() + p_width, p_coord.getY()));
	m_coordVector.push_back(Coord(p_coord.getX() + p_width, p_coord.getY() + p_height));
	m_coordVector.push_back(Coord(p_coord.getX(), p_coord.getY() + p_height));
	
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_RECTANGLE;
}

Rectangle::~Rectangle()
{
}

//TODO
bool Rectangle::checkCollision(Coord p_clickPoint, double p_radius) {
	//Rotate circle center from rectangle top-left corner standpoint
	double x = p_clickPoint.getX() - m_coordVector[0].getX();
	double y = p_clickPoint.getY() - m_coordVector[0].getY();
	double circleRotatedX = (x*cos(m_angle*PI / 180) - y*sin(m_angle*PI / 180)) + m_coordVector[0].getX();
	double circleRotatedY = (x*sin(m_angle*PI / 180) + y*cos(m_angle*PI / 180)) + m_coordVector[0].getY();

	//Hitbox detection
	double centerX = m_coordVector[0].getX() + (m_width / 2);
	double centerY = m_coordVector[0].getY() + (m_height / 2);	

	double distanceX = abs(circleRotatedX - centerX);
	double distanceY = abs(circleRotatedY - centerY);

	if (distanceX > ((m_width / 2) + p_radius)) return false;
	if (distanceY > ((m_height / 2) + p_radius)) return false;

	if (distanceX <= (m_width / 2)) return true;
	if (distanceY <= (m_height / 2)) return true;

	double distanceCornerToCenter = pow(distanceX - (m_width / 2), 2) + pow(distanceY - (m_height / 2), 2);
	return distanceCornerToCenter <= pow(p_radius, 2);
}

bool Rectangle::containedInRect(Coord p_topLeft, double p_width, double p_height) {
	double distanceX = 0;
	double distanceY = 0;
	for (Coord c : m_coordVector) {
		distanceX = c.getX() - p_topLeft.getX();
		distanceY = c.getY() - p_topLeft.getY();
		if (distanceX <= p_width && distanceY <= p_height && distanceX >= 0 && distanceY >= 0) return true;
	}
	return false;
}