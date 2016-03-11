#pragma once
#include "Shape2D.h"

namespace app {
	class Line2D : public Shape2D
	{
	public:
		Line2D(std::vector<Coord> p_coord, double p_angle, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill);
		~Line2D();
		bool checkCollision(Coord p_clickPoint, double p_radius) override;
		bool containedInRect(Coord p_topLeft, double p_width, double p_height) override;
	};
}
