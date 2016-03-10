#include "Obj2D.h"
#include <exception>
#include <iostream>

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

std::vector<Coord> Obj2D::getCoordVector() {
	return m_coordVector;
}

Coord Obj2D::getRotationCenter() {
	double xTot = 0;
	double yTot = 0;
	for (Coord c : m_coordVector) {
		xTot += c.getX();
		yTot += c.getY();
	}
	return Coord(xTot / m_coordVector.size(), yTot / m_coordVector.size());
}

void Obj2D::translate(double p_x, double p_y) {
	std::vector<Coord> newCoordVector;
	for (Coord c : m_coordVector) {
		c.addToCoord(p_x, p_y);
		newCoordVector.push_back(c);
	}
	m_coordVector = newCoordVector;
}

void Obj2D::resize(double p_percent) {

}

void Obj2D::rotate(Coord p_first, Coord p_sec) {
	Coord rotCenter = getRotationCenter();
	double vector1[]{ p_first.getX() - rotCenter.getX(), p_first.getY() - rotCenter.getY() };
	double vector2[]{ p_sec.getX() - rotCenter.getX(), p_sec.getY() - rotCenter.getY() };
	double angle = calculateAngle(vector1, vector2);
	angle = angle * getAngleSign(p_first, p_sec, rotCenter);
	rotate(rotCenter, angle);
}

void Obj2D::rotate(double p_degree) {
	
}

void Obj2D::rotate(Coord p_coord, double p_degree) {
	std::cout << p_degree << std::endl;
	std::vector<Coord> newCoordVector;
	double x = 0;
	double y = 0;
	for (Coord c : m_coordVector) {
		x = c.getX() - p_coord.getX();
		y = c.getY() - p_coord.getY();
		c.setX((x*cos(p_degree*PI / 180) - y*sin(p_degree*PI / 180)) + p_coord.getX());
		c.setY((x*sin(p_degree*PI / 180) + y*cos(p_degree*PI / 180)) + p_coord.getY());
		newCoordVector.push_back(c);
	}
	m_angle += p_degree;
	m_coordVector = newCoordVector;
}

bool Obj2D::containedInRect(Coord p_topLeft, double p_width, double p_height) {
	return false;
}

bool Obj2D::checkSelected(Coord p_clickPoint, double p_radius) {
	if (checkCollision(p_clickPoint, p_radius)) {
		m_isSelected = true;
		return true;
	}
	return false;
}

bool Obj2D::checkCollision(Coord p_clickPoint, double p_radius) {
	return false;
}

bool Obj2D::checkCollisionLineCircle(Coord p_coordA, Coord p_coordB, Coord p_clickPoint, double p_radius) {
	Coord collisionCoord = Coord(0, 0);
	double collisionX;
	double collisionY;
	double slope;
	double A;
	double B;
	double pointAX = p_coordA.getX();
	double pointAY = p_coordA.getY();
	double pointBX = p_coordB.getX();
	double pointBY = p_coordB.getY();

	if (pointBX - pointAX == 0) {
		collisionX = pointAX;
		collisionY = p_clickPoint.getY();
		collisionCoord = Coord((int)collisionX, (int)collisionY);
		if (calculateDistance(p_clickPoint, collisionCoord) > p_radius) return false;
		if ((collisionY <= pointAY && collisionY <= pointBY) ||
			(collisionY >= pointAY && collisionY >= pointBY)) return false;
	}
	else if (pointBY - pointAY == 0) {

		A = p_clickPoint.getX();
		B = p_clickPoint.getY();
		collisionX = A + sqrt(-(B*B) + (2 * B*pointAY) + (p_radius*p_radius) - (pointAY*pointAY));
		if (pointBY > B + p_radius || pointBY < B - p_radius) return false;
		if (calculateDistance(p_coordA, p_clickPoint) <= p_radius || calculateDistance(p_coordB, p_clickPoint) <= p_radius) return true;
		if ((collisionX < pointAX && collisionX < pointBX) ||
			(collisionX > pointAX && collisionX > pointBX)) return false;

	}
	else {
		slope = (pointBY - pointAY) / (pointBX - pointAX);
		double b = pointAY - slope*pointAX;
		double normal = -1 / slope;
		double b_normal = p_clickPoint.getY() - normal*p_clickPoint.getX();
		collisionX = (b - b_normal) / (normal - slope);
		collisionY = slope * collisionX + b;
		collisionCoord = Coord((int)collisionX, (int)collisionY);


		if (calculateDistance(p_clickPoint, collisionCoord) > p_radius) return false;
		if ((collisionX <= pointAX && collisionX <= pointBX) ||
			(collisionX >= pointAX && collisionX >= pointBX)) return false;
	}
	return true;
}

double Obj2D::calculateDistance(Coord p_coord1, Coord p_coord2) {
	double x2 = pow((p_coord1.getX() - p_coord2.getX()), 2);
	double y2 = pow((p_coord1.getY() - p_coord2.getY()), 2);
	return sqrt(x2 + y2);
}

double Obj2D::calculateAngle(double vector1[], double vector2[]) {
	double i = vector1[0] * vector2[0];
	double j = vector1[1] * vector2[1];
	double norm1 = sqrt(pow(vector1[0], 2) + pow(vector1[1], 2));
	double norm2 = sqrt(pow(vector2[0], 2) + pow(vector2[1], 2));
	double angle = acos((i + j) / (norm1*norm2))*(180 / PI);
	if(_isnan(angle) == 0) {
		return angle;
	}
	else {
		return 180;
	}
}

double Obj2D::getAngleSign(Coord p_first, Coord p_sec, Coord p_rotCenter) {
	double x = p_sec.getX() - p_first.getX();
	double y = p_sec.getY() - p_first.getY();
	double side = (p_sec.getX() + p_first.getX())/2 - p_rotCenter.getX();
	if (x >= 0 && y >= 0 && side >= 0) return 1;	
	else if (x <= 0 && y >= 0 && side >= 0) return 1;
	else if (x <= 0 && y <= 0 && side <= 0) return 1;
	else if (x >= 0 && y <= 0 && side <= 0) return 1;
	return -1;
}