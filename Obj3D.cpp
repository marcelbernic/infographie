#include "Obj3D.h"
#include <exception>
#include <iostream>

Obj3D::Obj3D(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill) {
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

ofColor Obj3D::getLineColor() {
    return  m_lineColor;
}

void Obj3D::setLineColor(ofColor p_lineColor) {
    m_lineColor = p_lineColor;
}

ofColor Obj3D::getLineColorSelected() {
    return m_lineColorSelected;
}

void Obj3D::setLineColorSelected(ofColor p_lineColorSelected) {
    m_lineColorSelected = p_lineColorSelected;
}

ofColor Obj3D::getColorFill() {
    return m_colorFill;
}

void Obj3D::setColorFill(ofColor p_colorFill) {
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
    return sqrt(x2 + y2 + z3);
}
bool Obj3D::checkCollisionLineCircle(Coord3D p_coordA, Coord3D p_coordB, Coord3D p_clickPoint, double p_radius){
    Coord3D collisionCoord = Coord3D(0, 0, 0);
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
        collisionCoord = Coord3D((int)collisionX, (int)collisionY, 0);
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
        collisionCoord = Coord3D((int)collisionX, (int)collisionY, 0);


        if (calculateDistance(p_clickPoint, collisionCoord) > p_radius) return false;
        if ((collisionX <= pointAX && collisionX <= pointBX) ||
            (collisionX >= pointAX && collisionX >= pointBX)) return false;
    }
    return true;
}

void Obj3D::draw(){

}
