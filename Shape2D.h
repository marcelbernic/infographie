#pragma once
#include "Obj2D.h"
class Shape2D : public Obj2D
{
public:
	Shape2D(double p_angle, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill);
	~Shape2D();
};

