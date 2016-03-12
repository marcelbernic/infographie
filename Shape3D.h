//#ifndef SHAPE3D_H
//#define SHAPE3D_H

//#endif // SHAPE3D_H


#pragma once
#include "Obj3D.h"

    class Shape3D : public Obj3D{

    public:
        Shape3D(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, ofColor p_colorFill);
        ~Shape3D();

    };
