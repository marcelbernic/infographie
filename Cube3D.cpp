#include "Cube3D.h"
using namespace app;

Cube3D::Cube3D(std::vector<Coord3D> p_coord, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill)
    : Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
    m_coordVector = p_coord;
    m_type = EnumVectorDrawMode::PRIMITIVE_CUBE;
    m_primitive.set(40, 40, 40);
    m_primitive.setPosition(p_coord[0].getX(), p_coord[0].getY(), p_coord[0].getZ());
    m_primitive.setSideColor(0, p_colorFill);
    m_primitive.setSideColor(1, p_colorFill);
    m_primitive.setSideColor(2, p_colorFill);
    m_primitive.setSideColor(3, p_colorFill);
    m_primitive.setSideColor(4, p_colorFill);
    m_primitive.setSideColor(5, p_colorFill);

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

ofColor Cube3D::getColorCube(){
    return m_colorCube;
}

void Cube3D::setColorCube(ofColor p_color){
    m_primitive.setSideColor(0, p_color);
    m_primitive.setSideColor(1, p_color);
    m_primitive.setSideColor(2, p_color);
    m_primitive.setSideColor(3, p_color);
    m_primitive.setSideColor(4, p_color);
    m_primitive.setSideColor(5, p_color);
}

ofVec3f Cube3D::getPosition(){
    return m_primitive.getPosition();

}

void Cube3D::setPositionX(int p_x){
    ofVec3f vect = getPosition();
    m_primitive.setPosition(p_x, vect.y, vect.z);
}

void Cube3D::setPositionY(int p_y){
    ofVec3f vect = getPosition();
    m_primitive.setPosition(vect.x, p_y, vect.z);
}

void Cube3D::setPositionZ(int p_z){
    ofVec3f vect = getPosition();
    m_primitive.setPosition(vect.x, vect.y, p_z);
}

void Cube3D::setRotateX(int p_rotx){
    ofVec3f vect(1, 0, 0);
    ofQuaternion quat(p_rotx, vect);
    m_primitive.setOrientation(quat);
}

void Cube3D::setRotateY(int p_roty){
    ofVec3f vect(0, 1, 0);
    ofQuaternion quat(p_roty, vect);
    m_primitive.setOrientation(quat);
}

void Cube3D::setRotateZ(int p_rotz){
    ofVec3f vect(0, 0, 1);
    ofQuaternion quat(p_rotz, vect);
    m_primitive.setOrientation(quat);
}

void Cube3D::draw() {
    m_primitive.draw();
}
