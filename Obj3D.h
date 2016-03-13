//#ifndef OBJ3D_H
//#define OBJ3D_H

//#endif // OBJ3D_H

#pragma once
#include "Coord3D.h"
#include <vector>
#include "primitive.h"
#include <cmath>
#include <stdlib.h>
#include "ofColor.h"
#include "ofxOpenCv.h"
#include "of3dGraphics.h"
#include "of3dPrimitives.h"
#include "of3dUtils.h"

#define PI (3.141592653589793)

class Obj3D
{
protected:
    int m_lineStroke;
    ofColor m_lineColor;
    ofColor m_lineColorSelected;
    ofColor m_colorFill;
    bool m_isSelected;
    std::vector<Coord3D> m_coordVector;
    EnumVectorDrawMode m_type;

public:
    Obj3D(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFills);
    ~Obj3D();

    void translate(double p_x, double p_y, double p_z);
    void resize(double p_percent); // 1 = 100%
    int getLineStroke();
    void setLineStroke(int p_lineStroke);
    ofColor getLineColor();
    void setLineColor(ofColor p_lineColor);
    ofColor getLineColorSelected();
    void setLineColorSelected(ofColor p_lineColorSelected);
    ofColor getColorFill();
    void setColorFill(ofColor p_colorFill);
    bool isSelected();
    void setSelected(bool p_selected);
    EnumVectorDrawMode getType();

    virtual void draw();

    double calculateDistance(Coord3D p_coord1, Coord3D p_coord2);
    bool checkCollisionLineCircle(Coord3D p_coordA, Coord3D p_coordB, Coord3D p_clickPoint, double p_radius);
};
