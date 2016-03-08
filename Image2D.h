#pragma once
#include "Obj2D.h"
#include "ofMain.h"
#include <string>

class Image2D : public Obj2D
{
private:
	ofImage * m_img;
	double m_width;
	double m_height;

public:
	Image2D(std::string p_url, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill);
	Image2D(std::string p_url, double p_width, double p_height, Coord p_pos, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFilld);
	~Image2D();
};

