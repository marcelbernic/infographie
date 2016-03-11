#pragma once
#include "Coord.h"
#include "ofColor.h"
#include <vector>
#include "primitive.h"
#include <cmath>
#include <stdlib.h>

#define PI (3.141592653589793)

class Obj2D
{
protected:
	std::vector<Coord> m_coordVector;
	double m_angle;
	int m_lineStroke;
	ofColor m_lineColor;
	ofColor m_lineColorSelected;
	ofColor m_colorFill;
	bool m_isSelected;
	EnumVectorDrawMode m_type;

public:
	Obj2D(double p_angle, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFills);
	~Obj2D();

	virtual void translate(double p_x, double p_y);
	virtual void resize(double p_percent); // 1 = 100%
	virtual void resize(Coord p_coord, double p_percent); // 1 = 100%
	void rotate(Coord p_first, Coord p_sec);
	void rotate(double p_degree); // rotate from shape center
	virtual void rotate(Coord p_coord, double p_degree); // rotate from coord

	double getAngle();
	void setAngle(double p_angle);
	int getLineStroke();
	void setLineStroke(int p_lineStroke);
	ofColor getLineColor();
	void setLineColor(int p_lineColor);
	ofColor getLineColorSelected();
	void setLineColorSelected(int p_lineColorSelected);
	ofColor getColorFill();
	void setColorFill(int p_colorFill);
	bool isSelected();
	virtual void setSelected(bool p_selected);
	EnumVectorDrawMode getType();
	std::vector<Coord> getCoordVector();

	double getAngleSign(Coord p_first, Coord p_sec, Coord p_rotCenter);
	Coord getRotationCenter();
	virtual bool containedInRect(Coord p_topLeft, double p_width, double p_height);
	virtual bool checkSelected(Coord p_clickPoint, double p_radius);
	virtual bool checkCollision(Coord p_clickPoint, double p_radius);
	bool checkCollisionLineCircle(Coord p_coordA, Coord p_coordB, Coord p_clickPoint, double p_radius);
	double calculateDistance(Coord p_coord1, Coord p_coord2);	
	double calculateAngle(double vector1[], double vector2[]);
};

