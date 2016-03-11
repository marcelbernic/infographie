#include "Coord3D.h"


Coord3D::Coord3D()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
}

Coord3D::Coord3D(double p_x, double p_y, double p_z)
{
    m_x = p_x;
    m_y = p_y;
    m_z = p_z;
}

Coord3D::Coord3D(int p_x, int p_y, int p_z) {
    m_x = (double)(p_x);
    m_y = (double)(p_y);
    m_z = (double)(p_z);
}

//Coord3D::Coord3D(Coord3D p_Coord3D) {
//	m_x = p_Coord3D.getX();
//	m_y = p_Coord3D.getY();
//}

double Coord3D::getX() {
    return m_x;
}

void Coord3D::setX(double p_x) {
    m_x = p_x;
}

void Coord3D::setX(int p_x) {
    m_x = (double)(p_x);
}

double Coord3D::getY() {
    return m_y;
}

void Coord3D::setY(double p_y) {
    m_y = p_y;
}

void Coord3D::setY(int p_y) {
    m_y = (double)(p_y);
}

double Coord3D::getZ() {
    return m_z;
}

void Coord3D::setZ(double p_z) {
    m_z = p_z;
}

void Coord3D::setZ(int p_z) {
    m_z = (double)(p_z);
}

void Coord3D::addToX(double p_x) {
    m_x += p_x;
}

void Coord3D::addToX(int p_x) {
    m_x += (double)(p_x);
}

void Coord3D::addToY(double p_y) {
    m_y += p_y;
}

void Coord3D::addToY(int p_y) {
    m_y += (double)(p_y);
}

void Coord3D::addToZ(double p_z) {
    m_z += p_z;
}

void Coord3D::addToZ(int p_z) {
    m_z += (double)(p_z);
}

void Coord3D::addToCoord(Coord3D p_Coord3D) {
    m_x += p_Coord3D.getX();
    m_y += p_Coord3D.getY();
    m_z += p_Coord3D.getZ();
}

void Coord3D::addToCoord(double p_x, double p_y, double p_z) {
    m_x += p_x;
    m_y += p_y;
    m_z += p_z;
}

Coord3D::~Coord3D()
{
}
