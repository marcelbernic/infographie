#include "Cercle.h"


Cercle::Cercle(double p_radius, Coord p_coord, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Shape2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_CIRCLE;
	m_radius = p_radius;
	m_coordVector.push_back(p_coord);
}


Cercle::~Cercle()
{
}

bool Cercle::checkCollision(Coord p_clickPoint, double p_radius) {
	return calculateDistance(p_clickPoint, m_coordVector[0]) <= (p_radius + m_radius);
}
