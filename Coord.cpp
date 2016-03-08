#include "Coord.h"



Coord::Coord(double p_x, double p_y)
{
	m_x = p_x;
	m_y = p_y;
}

Coord::Coord(int p_x, int p_y) {
	m_x = (double)(p_x);
	m_y = (double)(p_y);
}

//Coord::Coord(Coord p_coord) {
//	m_x = p_coord.getX();
//	m_y = p_coord.getY();
//}

double Coord::getX() {
	return m_x;
}

void Coord::setX(double p_x) {
	m_x = p_x;
}

void Coord::setX(int p_x) {
	m_x = (double)(p_x);
}

double Coord::getY() {
	return m_y;
}

void Coord::setY(double p_y) {
	m_y = p_y;
}

void Coord::setY(int p_y) {
	m_y = (double)(p_y);
}

void Coord::addToX(double p_x) {
	m_x += p_x;
}

void Coord::addToX(int p_x) {
	m_x += (double)(p_x);
}

void Coord::addToY(double p_y) {
	m_y += p_y;
}

void Coord::addToY(int p_y) {
	m_y += (double)(p_y);
}

void Coord::addToCoord(Coord p_coord) {
	m_x += p_coord.getX();
	m_y += p_coord.getY();
}

void Coord::addToCoord(double p_x, double p_y) {
	m_x += p_x;
	m_y += p_y;
}

Coord::~Coord()
{
}
