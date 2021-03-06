#pragma once
#include "Obj2D.h"
#include "ofMain.h"
#include <string>

namespace app {
	class Image2D : public Obj2D
	{
	private:
		ofImage m_img;
		double m_width;
		double m_height;

	public:
		Image2D(std::string p_url, double p_angle, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill);
		Image2D(std::string p_url, double p_width, double p_height, Coord p_pos, double p_angle, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFilld);
		~Image2D();

		void resize(Coord p_coord, double p_percent) override;
		ofImage getImage();
		double getWidth();
		double getHeight();
		bool checkCollision(Coord p_clickPoint, double p_radius) override;
		bool containedInRect(Coord p_topLeft, double p_width, double p_height) override;
	};
}
