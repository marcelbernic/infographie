#pragma once
#include "Shape3D.h"

namespace app {
    class CourbeNurbs : public Shape3D
    {
    private:
        std::vector<ofVec4f> m_controls;
        ofMesh m_mesh;
        ofColor m_colorCourbe;
    public:
        CourbeNurbs(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, double p_tesselation, vector<ofVec4f> p_controls, ofColor p_colorFill);
        ~CourbeNurbs();
        void setColorCurve(ofColor p_color);
        void setTesselation(double p_tesselation);
        vector<ofVec4f> getControlsPoints();
        void buildMesh();
        static ofVec3f nurbs(vector<ofVec4f> controls, float t);
        void draw() override;
        static float nCoef(int a, int b, float t, int M);
    };
}
