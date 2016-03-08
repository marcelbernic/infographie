#pragma once
#include "Shape2D.h"
#include "ofApp.h"


class Cercle : public Shape2D
{
private:
	double m_radius;

public:
	Cercle(double p_radius, Coord p_coord, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill);
	~Cercle();

	bool checkCollision(Coord p_clickPoint, double p_radius) override;
};

