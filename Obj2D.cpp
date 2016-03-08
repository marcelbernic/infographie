#include "Obj2D.h"

Obj2D::Obj2D(double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill) {
	m_angle = p_angle;
	m_lineStroke = p_lineStroke;
	m_lineColor = p_lineColor;
	m_lineColorSelected = p_lineColorSelected;
	m_colorFill = p_colorFill;
	m_isSelected = false;
}

Obj2D::~Obj2D()
{
}

double Obj2D::getAngle() {
	return m_angle;
}

void Obj2D::setAngle(double p_angle) {
	m_angle = p_angle;
}

int Obj2D::getLineStroke() {
	return m_lineStroke;
}

void Obj2D::setLineStroke(int p_lineStroke) {
	m_lineStroke = p_lineStroke;
}

int Obj2D::getLineColor() {
	return m_lineColor;
}

void Obj2D::setLineColor(int p_lineColor) {
	m_lineColor = p_lineColor;
}

int Obj2D::getLineColorSelected() {
	return m_lineColorSelected;
}

void Obj2D::setLineColorSelected(int p_lineColorSelected) {
	m_lineColorSelected = p_lineColorSelected;
}

int Obj2D::getColorFill() {
	return m_colorFill;
}

void Obj2D::setColorFill(int p_colorFill) {
	m_colorFill = p_colorFill;
}

bool Obj2D::isSelected() {
	return m_isSelected;
}

void Obj2D::setSelected(bool p_selected) {
	m_isSelected = p_selected;
}

EnumVectorDrawMode Obj2D::getType() {
	return m_type;
}

void Obj2D::translate(double p_x, double p_y) {
	for (Coord c : m_coordVector) {
		c.addToCoord(p_x, p_y);
	}
}

void Obj2D::resize(double p_percent) {

}

void Obj2D::rotate(double p_degree) {
	
}

void Obj2D::rotate(Coord p_coord, double p_degree) {
	double x = 0;
	double y = 0;
	for (Coord c : m_coordVector) {
		x = c.getX() - p_coord.getX();
		y = c.getY() - p_coord.getY();
		c.setX((x*cos(p_degree*PI / 180) - y*sin(p_degree*PI / 180)) + p_coord.getX());
		c.setY((x*sin(p_degree*PI / 180) + y*cos(p_degree*PI / 180)) + p_coord.getY());
	}
	m_angle += p_degree;
}

bool Obj2D::checkCollision(Coord p_clickPoint, double p_radius) {
	return false;
}

double Obj2D::calculateDistance(Coord p_coord1, Coord p_coord2) {
	double x2 = pow((p_coord1.getX() - p_coord2.getX()), 2);
	double y2 = pow((p_coord1.getY() - p_coord2.getY()), 2);
	return sqrt(x2 + y2);
}