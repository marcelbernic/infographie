#pragma once
#include "Coord.h"
#include <vector>
#include "primitive.h"

#define PI (3.141592653589793)

class Obj2D
{
protected:
	std::vector<Coord> m_coordVector;
	double m_angle;
	int m_lineStroke;
	int m_lineColor;
	int m_lineColorSelected;
	int m_colorFill;
	bool m_isSelected;
	EnumVectorDrawMode m_type;

public:
	Obj2D(double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFills);
	~Obj2D();

	void translate(double p_x, double p_y);
	void resize(double p_percent); // 1 = 100%
	virtual void rotate(double p_degree); // rotate from shape center
	void rotate(Coord p_coord, double p_degree); // rotate from coord

	double getAngle();
	void setAngle(double p_angle);
	int getLineStroke();
	void setLineStroke(int p_lineStroke);
	int getLineColor();
	void setLineColor(int p_lineColor);
	int getLineColorSelected();
	void setLineColorSelected(int p_lineColorSelected);
	int getColorFill();
	void setColorFill(int p_colorFill);
	bool isSelected();
	void setSelected(bool p_selected);
	EnumVectorDrawMode getType();

	virtual bool containedInRect(Coord p_topLeft, double p_width, double p_height);
	void checkSelected(Coord p_clickPoint, double p_radius);
	virtual bool checkCollision(Coord p_clickPoint, double p_radius);
	bool checkCollisionLineCircle(Coord p_coordA, Coord p_coordB, Coord p_clickPoint, double p_radius);
	double calculateDistance(Coord p_coord1, Coord p_coord2);	
	double calculateAngle(double vector1[], double vector2[]);
};

