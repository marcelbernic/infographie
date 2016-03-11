#include "Obj3D.h"
#include <exception>
#include <iostream>

Obj3D::Obj3D(int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill) {
    m_lineStroke = p_lineStroke;
    m_lineColor = p_lineColor;
    m_lineColorSelected = p_lineColorSelected;
    m_colorFill = p_colorFill;
    m_isSelected = false;
}

Obj3D::~Obj3D()
{
}

int Obj3D::getLineStroke() {
    return m_lineStroke;
}

void Obj3D::setLineStroke(int p_lineStroke) {
    m_lineStroke = p_lineStroke;
}

int Obj3D::getLineColor() {
    return m_lineColor;
}

void Obj3D::setLineColor(int p_lineColor) {
    m_lineColor = p_lineColor;
}

int Obj3D::getLineColorSelected() {
    return m_lineColorSelected;
}

void Obj3D::setLineColorSelected(int p_lineColorSelected) {
    m_lineColorSelected = p_lineColorSelected;
}

int Obj3D::getColorFill() {
    return m_colorFill;
}

void Obj3D::setColorFill(int p_colorFill) {
    m_colorFill = p_colorFill;
}

bool Obj3D::isSelected() {
    return m_isSelected;
}

void Obj3D::setSelected(bool p_selected) {
    m_isSelected = p_selected;
}

EnumVectorDrawMode Obj3D::getType() {
    return m_type;
}


void Obj3D::translate(double p_x, double p_y, double p_z) {
    std::vector<Coord3D> newCoordVector;
    for (Coord3D c : m_coordVector) {
        c.addToCoord(p_x, p_y, p_z);
        newCoordVector.push_back(c);
    }
    m_coordVector = newCoordVector;
}


double Obj3D::calculateDistance(Coord3D p_coord1, Coord3D p_coord2) {
    double x2 = pow((p_coord1.getX() - p_coord2.getX()), 2);
    double y2 = pow((p_coord1.getY() - p_coord2.getY()), 2);
    double z3 = pow((p_coord1.getZ() - p_coord2.getZ()), 2);
    return sqrt(x2 + y2);
}
