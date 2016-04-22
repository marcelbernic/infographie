#pragma once
#include "Shape3D.h"

namespace app {
    class CourbeCatmullRom : public Shape3D
    {
    private:
        std::vector<ofVec4f> m_controls;
        ofMesh m_mesh;
        ofColor m_colorCourbe;
    public:
        CourbeCatmullRom(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected, double p_tesselation, vector<ofVec4f> p_controls, ofColor p_colorFill);
        ~CourbeCatmullRom();
        void setColorCurve(ofColor p_color);
        void setTesselation(double p_tesselation);
        vector<ofVec4f> getControlsPoints();
        void buildMesh();
        void draw() override;
    };
}
