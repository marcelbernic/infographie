#pragma once
#include "Shape3D.h"
#include "CourbeNurbs.h"

namespace app {
    class SurfaceCoons : public Shape3D
    {
    private:
        std::vector<ofVec4f> m_controls;
        ofMesh m_mesh;
        ofColor m_colorCourbe;
    public:
        SurfaceCoons(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected,
                                           double p_tesselation, vector<ofVec4f> p_controls,
                                           ofColor p_colorFill);
        ~SurfaceCoons();
        void setColorCurve(ofColor p_color);
        void setTesselation(double p_tesselation);
        vector<ofVec4f> getControlsPoints();
        void buildMesh();
        void draw() override;
        int fact(int a);
        ofVec3f surfaceCoons(vector<ofVec4f> controls, vector<ofVec4f> controls2,
                                           vector<ofVec4f> controls3, vector<ofVec4f> controls4, float t1, float t2);
    };
}
