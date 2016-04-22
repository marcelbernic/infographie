#include "CourbeBezierCubique.h"
using namespace app;

CourbeBezierCubique::CourbeBezierCubique(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected,
                                   double p_tesselation, vector<ofVec4f> p_controls,
                                   ofColor p_colorFill): Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected,
                                                                 p_colorFill){
    m_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    m_mesh.enableColors();
    m_shaderMode = ShaderMode::NONE;
    m_controls = p_controls;
    m_type = EnumVectorDrawMode::PRIMITIVE_COURBE_BEZIERCUBIQUE;
    m_tesselation = p_tesselation;
    m_colorCourbe = p_colorFill;
    buildMesh();
}

vector<ofVec4f> CourbeBezierCubique::getControlsPoints(){
    return m_controls;
}

void CourbeBezierCubique::setTesselation(double p_tesselation){
    m_tesselation = p_tesselation;
    m_mesh.clear();
    buildMesh();
}

void CourbeBezierCubique::buildMesh(){


    int nSteps = floor(m_tesselation) + 1;
    ofVec3f ret;

    for(int i = 0; i < nSteps; i++){
        float time1 = (float)i / (float)(nSteps - 1);  // time between 0 and 1

        int N = m_controls.size() - 1;

        ret.x = 0;
        ret.y = 0;
        ret.z = 0;

        for(int i = 0; i <= N; i++){

            ret.x = (float)ret.x + (float)((float)fact(N)/((float)((float)fact(i)*(float)fact(N-i))))*(float)pow(time1, i)*(float)pow(1-time1, N-i)*(float)(m_controls[i].x);
            ret.y = (float)ret.y + (float)((float)fact(N)/((float)((float)fact(i)*(float)fact(N-i))))*(float)pow(time1, i)*(float)pow(1-time1, N-i)*(float)(m_controls[i].y);
            ret.z = (float)ret.z + (float)((float)fact(N)/((float)((float)fact(i)*(float)fact(N-i))))*(float)pow(time1, i)*(float)pow(1-time1, N-i)*(float)(m_controls[i].z);

        }



        m_mesh.addVertex(ofPoint(ret.x, ret.y, ret.z));
        m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255, (float)m_colorCourbe.g/(float)255, (float)m_colorCourbe.b/(float)255));  // add a color at that vertex

    }


}

void CourbeBezierCubique::draw(){
    m_mesh.draw();

}

void CourbeBezierCubique::setColorCurve(ofColor p_color){
    m_colorCourbe = p_color;
    m_mesh.clear();
    buildMesh();

}

int CourbeBezierCubique::fact(int a){
    int ret = 1;
    if(a == 0){
        ret = 1;
    }
    else{
        for(int i = 1; i <= a; i++){
            ret = ret*i;
        }
    }

    return ret;
}


