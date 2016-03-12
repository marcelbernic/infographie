#ifndef OBJ3D_H
#define OBJ3D_H

#endif // OBJ3D_H

#pragma once
#include "Coord3D.h"
#include <vector>
#include "primitive.h"
#include <cmath>
#include <stdlib.h>
#include "ofApp.h"

#define PI (3.141592653589793)

class Obj3D
{
protected:
    int m_lineStroke;
    int m_lineColor;
    int m_lineColorSelected;
    int m_colorFill;
    bool m_isSelected;
    std::vector<Coord3D> m_coordVector;
    EnumVectorDrawMode m_type;
    ofMesh mesh;

public:
    Obj3D(int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFills);
    ~Obj3D();

    void translate(double p_x, double p_y, double p_z);
    void resize(double p_percent); // 1 = 100%
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

    double calculateDistance(Coord3D p_coord1, Coord3D p_coord2);
};
