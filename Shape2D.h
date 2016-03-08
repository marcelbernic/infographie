#pragma once
#include "Obj2D.h"
class Shape2D : public Obj2D
{
public:
	Shape2D(double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill);
	~Shape2D();
};

