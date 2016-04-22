#include "SurfaceBezierCubique.h"
using namespace app;

SurfaceBezierCubique::SurfaceBezierCubique(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected,
                                   double p_tesselation, vector<ofVec4f> p_controls,
                                   ofColor p_colorFill): Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected,
                                                                 p_colorFill){
    m_mesh.setMode(OF_PRIMITIVE_POINTS);
    m_mesh.enableColors();
    m_shaderMode = ShaderMode::NONE;
    m_controls = p_controls;
    m_type = EnumVectorDrawMode::PRIMITIVE_SURFACE_BEZIERCUBIQUE;
    m_tesselation = p_tesselation;
    m_colorCourbe = p_colorFill;
    buildMesh();
}

vector<ofVec4f> SurfaceBezierCubique::getControlsPoints(){
    return m_controls;
}

void SurfaceBezierCubique::setTesselation(double p_tesselation){
    m_tesselation = p_tesselation;
    m_mesh.clear();
    buildMesh();
}

void SurfaceBezierCubique::buildMesh(){


    int nSteps = m_tesselation;
    ofVec3f ret;

    for(int i = 0; i < nSteps; i++){
        float time1 = (float)i / (float)(nSteps - 1);  // time between 0 and 1
        for(int j = 0; j < nSteps; j++){
            float time2 = (float)j / (float)(nSteps - 1);

            int N = sqrt(m_controls.size()) - 1;

            ret.x = 0;
            ret.y = 0;
            ret.z = 0;

            for(int ii = 0; ii <= N; ii++){
                for(int jj = 0; jj <= N; jj++){

                    ret.x = (float)ret.x + (float)((float)fact(N)/((float)((float)fact(ii)*(float)fact(N-ii))))*(float)pow(time1, ii)*(float)pow(1-time1, N-ii)*(float)((float)fact(N)/((float)((float)fact(jj)*(float)fact(N-jj))))*(float)pow(time2, jj)*(float)pow(1-time2, N-jj)*(float)(m_controls[ii*(N+1)+jj].x);
                    ret.y = (float)ret.y + (float)((float)fact(N)/((float)((float)fact(ii)*(float)fact(N-ii))))*(float)pow(time1, ii)*(float)pow(1-time1, N-ii)*(float)((float)fact(N)/((float)((float)fact(jj)*(float)fact(N-jj))))*(float)pow(time2, jj)*(float)pow(1-time2, N-jj)*(float)(m_controls[ii*(N+1)+jj].y);
                    ret.z = (float)ret.z + (float)((float)fact(N)/((float)((float)fact(ii)*(float)fact(N-ii))))*(float)pow(time1, ii)*(float)pow(1-time1, N-ii)*(float)((float)fact(N)/((float)((float)fact(jj)*(float)fact(N-jj))))*(float)pow(time2, jj)*(float)pow(1-time2, N-jj)*(float)(m_controls[ii*(N+1)+jj].z);
                }
            }



            m_mesh.addVertex(ofPoint(ret.x, ret.y, ret.z));
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255, (float)m_colorCourbe.g/(float)255, (float)m_colorCourbe.b/(float)255));  // add a color at that vertex

        }
    }


}

void SurfaceBezierCubique::draw(){
    m_mesh.draw();

}

void SurfaceBezierCubique::setColorCurve(ofColor p_color){
    m_colorCourbe = p_color;
    m_mesh.clear();
    buildMesh();

}

int SurfaceBezierCubique::fact(int a){
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


