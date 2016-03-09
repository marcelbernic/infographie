#include "Rectangle.h"


Rectangle::Rectangle(Coord p_coord, double p_width, double p_height, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Shape2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_coordVector = std::vector<Coord>();
	m_coordVector.push_back(p_coord);
	m_width = p_width;
	m_height = p_height;
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