#pragma once

#include "Shape3D.h"

namespace app {
    class ArretTriangle
    {
    public:
        ofVec3f pt1;
        ofVec3f pt2;
        ofVec3f pt3;
        ofVec3f pt4;
        ofVec3f pt5;
        ofVec3f pt6;

        ofVec3f pt1Adj;
        ofVec3f pt2Adj;

        ArretTriangle(ofVec3f p_pt1, ofVec3f p_pt2, ofVec3f p_pt3, ofVec3f p_pt4, ofVec3f p_pt5,
                      ofVec3f p_pt6, ofVec3f p_pt7, ofVec3f p_pt8);

        static vector<ofVec3f> get2Triangles(vector<ArretTriangle> p_vect, ofVec3f p_pt1, ofVec3f p_pt2);
        ~ArretTriangle();
    };
}

