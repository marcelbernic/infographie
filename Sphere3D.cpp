#include "Sphere3D.h"
using namespace app;

Sphere3D::Sphere3D(double p_dim, std::vector<Coord3D> p_coord, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill)
    : Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_shaderMode = ShaderMode::NONE;
    m_coordVector = p_coord;
    m_type = EnumVectorDrawMode::PRIMITIVE_SPHERE;
    m_primitive.set(p_dim, 50);
    m_primitive.setPosition(p_coord[0].getX(), p_coord[0].getY(), p_coord[0].getZ());

}


Sphere3D::~Sphere3D()
{
}

//TODO
bool Sphere3D::checkCollision(Coord3D p_clickPoint, double p_radius) {
    return checkCollisionLineCircle(m_vector3D[0], m_vector3D[1], p_clickPoint, p_radius);
}

bool Sphere3D::containedInRect(Coord3D p_topLeft, double p_width, double p_height) {
    double distanceX = 0;
    double distanceY = 0;
    for (Coord3D c : m_coordVector) {
        distanceX = c.getX() - p_topLeft.getX();
        distanceY = c.getY() - p_topLeft.getY();
        if (distanceX <= p_width && distanceY <= p_height && distanceX >= 0 && distanceY >= 0) return true;
    }
    return false;
}

ofColor Sphere3D::getColorSphere(){
    return m_colorSphere;
}

void Sphere3D::setColorSphere(ofColor p_color){
    m_colorSphere = p_color;

}

ofVec3f Sphere3D::getPosition(){
    return m_primitive.getPosition();

}

void Sphere3D::setPositionX(int p_x){
    ofVec3f vect = getPosition();
    m_primitive.setPosition(p_x, vect.y, vect.z);
}

void Sphere3D::setPositionY(int p_y){
    ofVec3f vect = getPosition();
    m_primitive.setPosition(vect.x, p_y, vect.z);
}

void Sphere3D::setPositionZ(int p_z){
    ofVec3f vect = getPosition();
    m_primitive.setPosition(vect.x, vect.y, p_z);
}

void Sphere3D::setRotateX(int p_rotx){
    ofVec3f vect(1, 0, 0);
    ofQuaternion quat(p_rotx, vect);
    m_primitive.setOrientation(quat);
}

void Sphere3D::setRotateY(int p_roty){
    ofVec3f vect(0, 1, 0);
    ofQuaternion quat(p_roty, vect);
    m_primitive.setOrientation(quat);
}

void Sphere3D::setRotateZ(int p_rotz){
    ofVec3f vect(0, 0, 1);
    ofQuaternion quat(p_rotz, vect);
    m_primitive.setOrientation(quat);
}

void Sphere3D::setDimension(double p_dimension){
    m_primitive.setRadius(p_dimension);
}

void Sphere3D::draw() {
    ofPushMatrix();
    ofColor color;
    color.r = m_colorSphere.r;
    color.g = m_colorSphere.g;
    color.b = m_colorSphere.b;
    ofSetColor(color.r, color.g, color.b);
    ofFill();
    if(isCloud()){
        m_primitive.drawVertices();
    }
    else{
        m_primitive.draw();
    }
    ofPopMatrix();
}
