#pragma once
#include "Shape2D.h"
namespace app {
	class Triangle : public Shape2D
	{
	public:
		Triangle(std::vector<Coord> p_coord, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill);
		~Triangle();

		bool checkCollision(Coord p_clickPoint, double p_radius) override;
		bool containedInRect(Coord p_topLeft, double p_width, double p_height) override;
	};
}

