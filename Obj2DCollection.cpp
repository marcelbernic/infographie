#include "Obj2DCollection.h"

using namespace app;

Obj2DCollection::Obj2DCollection(std::vector<Obj2D*> p_objVector)
	: Obj2D(0, 0, 0, 0, 0) {
	m_objVector = p_objVector;
	for (Obj2D* o : p_objVector) {
		for (Coord c : o->getCoordVector()) {
			m_coordVector.push_back(c);
		}
	}
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_COLLECTION;
}


Obj2DCollection::~Obj2DCollection()
{
}

std::vector<Obj2D*> Obj2DCollection::getObjVector() {
	return m_objVector;
}

void Obj2DCollection::setSelected(bool p_selected) {
	m_isSelected = p_selected;
	for (Obj2D* o : m_objVector) {
		o->setSelected(p_selected);
	}
}

bool Obj2DCollection::checkSelected(Coord p_clickPoint, double p_radius) {
	if (checkCollision(p_clickPoint, p_radius)) {
		setSelected(true);
		return true;
	}
	setSelected(false);
	return false;
}

bool Obj2DCollection::checkCollision(Coord p_clickPoint, double p_radius) {
	for (Obj2D* o : m_objVector) {
		if (o->checkCollision(p_clickPoint, p_radius)) return true;
	}
	return false;
}

bool Obj2DCollection::containedInRect(Coord p_topLeft, double p_width, double p_height) {
	for (Obj2D* o : m_objVector) {
		if (o->containedInRect(p_topLeft, p_width, p_height)) return true;
	}
	return false;
}

void Obj2DCollection::rotate(Coord p_coord, double p_degree) {
	for (Obj2D* o : m_objVector) {
		o->rotate(p_coord, p_degree);
	}
}

void Obj2DCollection::translate(double p_x, double p_y) {
	for (Obj2D* o : m_objVector) {
		o->translate(p_x, p_y);
	}
	std::vector<Coord> newCoordVector;
	for (Coord c : m_coordVector) {
		c.addToCoord(p_x, p_y);
		newCoordVector.push_back(c);
	}
	m_coordVector = newCoordVector;
}