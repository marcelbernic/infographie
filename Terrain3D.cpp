#include "Terrain3D.h"

using namespace app;

Terrain3D::Terrain3D(std::vector<Coord3D> p_coord, string p_url, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill)
	: Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_shaderMode = ShaderMode::NONE;
	m_coordVector = p_coord;
	m_type = EnumVectorDrawMode::PRIMITIVE_TERRAIN;

	m_img.load(p_url);
	m_width = m_img.getWidth();
	m_height = m_img.getHeight();

	m_primitive.setPosition(p_coord[0].getX(), p_coord[0].getY(), p_coord[0].getZ());
	m_primitive.setWidth(m_width);
	m_primitive.setHeight(m_height);
	m_primitive.setResolution(64, 64);

	m_lineStroke;
	m_lineColor;
	m_lineColorSelected ;
	m_colorFill;
	m_isSelected = false;
	m_cloud = false;
	rotationX = 0;
	rotationY = 0;
	rotationZ = 0;

	prepareToDraw();
}


Terrain3D::~Terrain3D(){
}

ofVec3f Terrain3D::getPosition() {
	return m_primitive.getPosition();

}

void Terrain3D::setPositionX(int p_x) {
	ofVec3f vect = getPosition();
	m_primitive.setPosition(p_x, vect.y, vect.z);
	m_coordVector[0].setX(p_x);
}

void Terrain3D::setPositionY(int p_y) {
	ofVec3f vect = getPosition();
	m_primitive.setPosition(vect.x, p_y, vect.z);
	m_coordVector[0].setY(p_y);
}

void Terrain3D::setPositionZ(int p_z) {
	ofVec3f vect = getPosition();
	m_primitive.setPosition(vect.x, vect.y, p_z);
	m_coordVector[0].setZ(p_z);
}

void Terrain3D::setRotateX(int p_rotx) {
	ofVec3f vect(1, 0, 0);
	ofQuaternion quat(p_rotx, vect);
	m_primitive.setOrientation(quat);
	rotationX = p_rotx;
}

void Terrain3D::setRotateY(int p_roty) {
	ofVec3f vect(0, 1, 0);
	ofQuaternion quat(p_roty, vect);
	m_primitive.setOrientation(quat);
	rotationY = p_roty;
}

void Terrain3D::setRotateZ(int p_rotz) {
	ofVec3f vect(0, 0, 1);
	ofQuaternion quat(p_rotz, vect);
	m_primitive.setOrientation(quat);
	rotationZ = p_rotz;
}

void Terrain3D::setDimension(double p_dimension) {
	m_primitive.setWidth(p_dimension);
	m_primitive.setHeight(p_dimension);
}

void Terrain3D::draw() {
	if (isCloud()) {
		m_primitive.drawVertices();
	}
	else {
		m_primitive.draw();
	}
}

void Terrain3D::prepareToDraw() {
	m_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	int skip = 1;
	int width = m_img.getWidth();
	int height = m_img.getHeight();
	for (int y = 0; y < height - skip; y += skip) {
		for (int x = 0; x < width - skip; x += skip) {
			ofVec3f nw = getVertexFromImg(m_img, x, y);
			ofVec3f ne = getVertexFromImg(m_img, x + skip, y);
			ofVec3f sw = getVertexFromImg(m_img, x, y + skip);
			ofVec3f se = getVertexFromImg(m_img, x + skip, y + skip);

			addFace(m_mesh, nw, ne, se, sw);
		}
	}
}

void Terrain3D::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c) {
	ofVec3f normal = ((b - a).cross(c - a)).normalize();
	mesh.addNormal(normal);
	mesh.addVertex(a);
	mesh.addNormal(normal);
	mesh.addVertex(b);
	mesh.addNormal(normal);
	mesh.addVertex(c);
}

//--------------------------------------------------------------
void Terrain3D::addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

//--------------------------------------------------------------
ofVec3f Terrain3D::getVertexFromImg(ofFloatImage& img, int x, int y) {
	return ofVec3f(x, y, 64 * img.getColor(x, y).getBrightness());
}

Coord3D Terrain3D::getOtherPosition() {
	return m_coordVector[0];
}