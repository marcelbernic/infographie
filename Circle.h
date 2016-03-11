#pragma once
#include "Shape2D.h"

namespace app {
	class Circle : public Shape2D
	{
	private:
		double m_radius;

	public:
		Circle(Coord p_coord, double p_radius, double p_angle, int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill);
		~Circle();

		void resize(Coord p_coord, double p_percent) override; // 1 = 100%
		bool checkCollision(Coord p_clickPoint, double p_radius) override;
		bool containedInRect(Coord p_topLeft, double p_width, double p_height) override;
		double getRadius();
	};
}

