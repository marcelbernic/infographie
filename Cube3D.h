#pragma once
#include "Shape3D.h"

namespace app {
    class Cube3D : public Shape3D
    {
    private:
        std::vector<Coord3D> m_vector3D;
        ofBoxPrimitive m_primitive;
        ofColor m_colorCube;
        double m_dimension;
    public:
        Cube3D(double p_dim, std::vector<Coord3D> p_coord, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill);
        ~Cube3D();
        void setColorCube(ofColor p_color);
        void setPositionX(int p_x);
        void setPositionY(int p_y);
        void setPositionZ(int p_z);
        void setRotateX(int p_x);
        void setRotateY(int p_y);
        void setRotateZ(int p_z);
        void setDimension(double p_dimension) override;
        double getDimension();
        ofVec3f getPosition();
        ofColor getColorCube();
        bool checkCollision(Coord3D p_clickPoint, double p_radius);
        bool containedInRect(Coord3D p_topLeft, double p_width, double p_height);
        void draw() override;
    };
}
