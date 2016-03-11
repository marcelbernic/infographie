#include "Image2D.h"
using namespace app;

Image2D::Image2D(std::string p_url, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Obj2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_img = ofImage();
	m_img.load(p_url);
	m_width = m_img.getWidth();
	m_height = m_img.getHeight();
	m_coordVector = vector<Coord>();
	m_coordVector.push_back(Coord(0,0));
	m_coordVector.push_back(Coord(m_width, 0.0));
	m_coordVector.push_back(Coord(0.0, m_height));
	m_coordVector.push_back(Coord(m_width, m_height));
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_IMAGE;
}

Image2D::Image2D(std::string p_url, double p_width, double p_height, Coord p_pos, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Obj2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_img = ofImage();
	std::cout <<"url: " << p_url << std::endl;
	m_img.load(p_url);
	m_width = p_width;
	m_height = p_height;
	m_coordVector = vector<Coord>();
	m_coordVector.push_back(p_pos);
	m_coordVector.push_back(Coord(p_pos.getX() + p_width, p_pos.getY()));
	m_coordVector.push_back(Coord(p_pos.getX(), p_pos.getY() + p_height));
	m_coordVector.push_back(Coord(p_pos.getX() + p_width, p_pos.getY() + p_height));
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_IMAGE;
}

Image2D::~Image2D()
{
}

ofImage Image2D::getImage() {
	return m_img;
}

double Image2D::getWidth() {
	return m_width;
}

double Image2D::getHeight() {
	return m_height;
}

void Image2D::resize(Coord p_coord, double p_percent) {
	Obj2D::resize(p_coord, p_percent);
	m_width *= p_percent;
	m_height *= p_percent;
}

//TODO
bool Image2D::checkCollision(Coord p_clickPoint, double p_radius) {
	//Rotate circle center from rectangle top-left corner standpoint
	double x = p_clickPoint.getX() - m_coordVector[0].getX();
	double y = p_clickPoint.getY() - m_coordVector[0].getY();
	double circleRotatedX = (x*cos(m_angle*PI / 180) - y*sin(m_angle*PI / 180)) + m_coordVector[0].getX();
	double circleRotatedY = (x*sin(m_angle*PI / 180) + y*cos(m_angle*PI / 180)) + m_coordVector[0].getY();

	//Hitbox detection
	double centerX = m_coordVector[0].getX() + (m_width / 2);
	double centerY = m_coordVector[0].getY() + (m_height / 2);

	double distanceX = abs(circleRotatedX - centerX);
	double distanceY = abs(circleRotatedY - centerY);

	if (distanceX > ((m_width / 2) + p_radius)) return false;
	if (distanceY > ((m_height / 2) + p_radius)) return false;

	if (distanceX <= (m_width / 2)) return true;
	if (distanceY <= (m_height / 2)) return true;

	double distanceCornerToCenter = pow(distanceX - (m_width / 2), 2) + pow(distanceY - (m_height / 2), 2);
	return distanceCornerToCenter <= pow(p_radius, 2);
}

bool Image2D::containedInRect(Coord p_topLeft, double p_width, double p_height) {
	double distanceX = 0;
	double distanceY = 0;
	for (Coord c : m_coordVector) {
		distanceX = c.getX() - p_topLeft.getX();
		distanceY = c.getY() - p_topLeft.getY();
		if (distanceX <= p_width && distanceY <= p_height && distanceX >= 0 && distanceY >= 0) return true;
	}
	return false;
}