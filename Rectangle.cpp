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
	return true;
}