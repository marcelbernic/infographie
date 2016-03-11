#ifndef CLOUDPOINTS_CPP
#define CLOUDPOINTS_CPP

#endif // CLOUDPOINTS_CPP

#include "CloudPoints.h"
using namespace app;

CloudPoints::CloudPoints(int p_lineStroke, int p_lineColor,
                         int p_lineColorSelected, int p_colorFill, Coord3D p_pos, double width, double height, double depth)
    : Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected, p_colorFill) {
    m_position.setX(p_pos.getX());
    m_width = width;
    m_height = height;
    m_depth = depth;
}

void CloudPoints::draw(){
   // m_mesh.draw();
}

CloudPoints::~CloudPoints(){

}
