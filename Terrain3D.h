#pragma once
#include "Shape3D.h"

namespace app {
	class Terrain3D : public Shape3D
	{
	private:
		
		ofPlanePrimitive m_primitive;

	public:
		ofMesh m_mesh;
		ofFloatImage m_img;
		double m_width;
		double m_height;
		Terrain3D(std::vector<Coord3D> p_coord, string p_url, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill);
		~Terrain3D();

		void setPositionX(int p_x);
		void setPositionY(int p_y);
		void setPositionZ(int p_z);
		void setRotateX(int p_x);
		void setRotateY(int p_y);
		void setRotateZ(int p_z);
		void setDimension(double p_dimension) override;
		ofVec3f getPosition();
		void draw() override;
		void Terrain3D::prepareToDraw();
		void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c);
		void addFace(ofMesh& mesh, ofVec3f a, ofVec3f b, ofVec3f c, ofVec3f d);
		ofVec3f getVertexFromImg(ofFloatImage& img, int x, int y);
	};	
}

