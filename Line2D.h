#pragma once
#include "Shape2D.h"
class Line2D : public Shape2D
{
public:
	Line2D(std::vector<Coord> p_coord, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill);
	~Line2D();
};

