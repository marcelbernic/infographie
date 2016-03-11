#ifndef CLOUDPOINTS_H
#define CLOUDPOINTS_H

#endif // CLOUDPOINTS_H

#pragma once
#include "Shape3D.h"

namespace app {
    class CloudPoints : public Shape3D
    {
    private:
        double m_width;
        double m_height;
        double m_depth;
        Coord3D m_position;

    public:
        CloudPoints(int p_lineStroke, int p_lineColor,
                    int p_lineColorSelected, int p_colorFill,Coord3D p_pos, double width, double height, double depth);
        void draw();
        ~CloudPoints();

    };
}
