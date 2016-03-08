#include "Image2D.h"

Image2D::Image2D(std::string p_url, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Obj2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_img = new ofImage();
	m_img->load(p_url);
	m_width = m_img->getWidth();
	m_height = m_img->getHeight();
	m_coordVector = vector<Coord>();
	m_coordVector.push_back(Coord(0,0));
	m_type = EnumVectorDrawMode::VECTOR_PRIMITIVE_IMAGE;
}

Image2D::Image2D(std::string p_url, double p_width, double p_height, Coord p_pos, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill)
	: Obj2D(p_angle, p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
	m_img = new ofImage();
	m_img->load(p_url);
	m_img->resize((int)(p_width), (int)(p_height));
	m_coordVector = vector<Coord>();
	m_coordVector.push_back(p_pos);
}

Image2D::~Image2D()
{
}