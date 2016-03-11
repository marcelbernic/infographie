#ifndef SHAPE3D_H
#define SHAPE3D_H

#endif // SHAPE3D_H

#ifndef CLOUDPOINTS_H
#define CLOUDPOINTS_H

#endif // CLOUDPOINTS_H

#pragma once
#include "Shape3D.h"
#include "Coord3D.h"
#include "Obj3D.h"

namespace app {
    class Shape3D : public Obj3D{

    public:
        Shape3D(int p_lineStroke, int p_lineColor, int p_lineColorSelected, int p_colorFill);
        ~Shape3D();

    };
}
