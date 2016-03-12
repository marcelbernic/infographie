#pragma once
#include "Shape3D.h"

namespace app {
    class Cube3D : public Shape3D
    {
    private:
        std::vector<Coord3D> m_vector3D;
    public:
        Cube3D(std::vector<Coord3D> p_coord, int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill);
        ~Cube3D();
        bool checkCollision(Coord3D p_clickPoint, double p_radius);
        bool containedInRect(Coord3D p_topLeft, double p_width, double p_height);
    };
}

