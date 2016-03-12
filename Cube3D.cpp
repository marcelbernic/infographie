#include "Cube3D.h"
using namespace app;

Cube3D::Cube3D(std::vector<Coord3D> p_coord, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill)
    : Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
    m_coordVector = p_coord;
    m_type = EnumVectorDrawMode::PRIMITIVE_CUBE;
}


Cube3D::~Cube3D()
{
}

//TODO
bool Cube3D::checkCollision(Coord3D p_clickPoint, double p_radius) {
    return checkCollisionLineCircle(m_vector3D[0], m_vector3D[1], p_clickPoint, p_radius);
}

bool Cube3D::containedInRect(Coord3D p_topLeft, double p_width, double p_height) {
    double distanceX = 0;
    double distanceY = 0;
    for (Coord3D c : m_coordVector) {
        distanceX = c.getX() - p_topLeft.getX();
        distanceY = c.getY() - p_topLeft.getY();
        if (distanceX <= p_width && distanceY <= p_height && distanceX >= 0 && distanceY >= 0) return true;
    }
    return false;
}
