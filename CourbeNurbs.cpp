#include "CourbeNurbs.h"
using namespace app;

CourbeNurbs::CourbeNurbs(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected,
                                   double p_tesselation, vector<ofVec4f> p_controls,
                                   ofColor p_colorFill): Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected,
                                                                 p_colorFill){
    m_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    m_mesh.enableColors();
    m_shaderMode = ShaderMode::NONE;
    m_controls = p_controls;
    m_type = EnumVectorDrawMode::PRIMITIVE_COURBE_NURBS;
    m_tesselation = p_tesselation;
    m_colorCourbe = p_colorFill;
    buildMesh();
}

vector<ofVec4f> CourbeNurbs::getControlsPoints(){
    return m_controls;
}

void CourbeNurbs::setTesselation(double p_tesselation){
    m_tesselation = p_tesselation;
    m_mesh.clear();
    buildMesh();
}

void CourbeNurbs::buildMesh(){
    ofVec3f ret;


    int nSteps = floor(m_tesselation) + 1;

    for(int i = 0; i < nSteps; i++){
        float time1 = (float)i / (float)(nSteps - 1);  // time between 0 and 1
        ret.x = 0;
        ret.y = 0;
        ret.z = 0;

        int N = m_controls.size();

        float den = 0;
        int M = N + 3;


        for(int i = 1; i <= N; i++){
            //int i = 1; // 1.. N-2

            ret.x = ret.x + nCoef(i-1, 3, time1, M)*m_controls[i-1].w*m_controls[i-1].x;

            ret.y = ret.y + nCoef(i-1, 3, time1, M)*m_controls[i-1].w*m_controls[i-1].y;

            ret.z = ret.z + nCoef(i-1, 3, time1, M)*m_controls[i-1].w*m_controls[i-1].z;

            den = den + nCoef(i-1, 3, time1, M)*m_controls[i-1].w;

        }


        if(den == 0){
            ret.x = 0;
            ret.y = 0;
            ret.z = 0;
        }
        else{
            ret.x = ret.x/den;
            ret.y = ret.y/den;
            ret.z = ret.z/den;
        }

        if(time1 == 0){
            ret.x = m_controls[0].x;
            ret.y = m_controls[0].y;
            ret.z = m_controls[0].z;
            m_mesh.addVertex(ofPoint(ret.x, ret.y, ret.z));
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255, (float)m_colorCourbe.g/(float)255, (float)m_colorCourbe.b/(float)255));
        }

        else if(time1 == 1){
            ret.x = m_controls.back().x;
            ret.y = m_controls.back().y;
            ret.z = m_controls.back().z;
            m_mesh.addVertex(ofPoint(ret.x, ret.y, ret.z));
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255, (float)m_colorCourbe.g/(float)255, (float)m_colorCourbe.b/(float)255));
        }
        else{

            m_mesh.addVertex(ofPoint(ret.x, ret.y, ret.z));
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255, (float)m_colorCourbe.g/(float)255, (float)m_colorCourbe.b/(float)255));  // add a color at that vertex
        }

      }


}

void CourbeNurbs::draw(){
    m_mesh.draw();

}

void CourbeNurbs::setColorCurve(ofColor p_color){
    m_colorCourbe = p_color;
    m_mesh.clear();
    buildMesh();

}

float CourbeNurbs::nCoef(int a, int b, float t, int M){
    float ret;
    if(b == 0){

        if((float)a/(float)M <= t && t < (float)(a+1)/(float)M){
            ret = 1;

        }
        else{
            ret = 0;
        }

    }
    else{

        ret = (t - (float)a/M)*nCoef(a, b - 1, t, M)/((float)(a+b)/(float)M - (float)a/(float)M) +
                ((float)(a + b + 1)/(float)M - t)*nCoef(a + 1, b - 1, t, M)/((float)(a + b + 1)/(float)M - (float)(a + 1)/(float)M);
    }


    return ret;

}

ofVec3f CourbeNurbs::nurbs(vector<ofVec4f> controls, float t){

    ofVec3f ret;

    ret.x = 0;
    ret.y = 0;
    ret.z = 0;

    if(t == 0){
        ret.x = controls[0].x;
        ret.y = controls[0].y;
        ret.z = controls[0].z;
        return ret;

    }
    if(t == 1){
        ret.x = controls.back().x;
        ret.y = controls.back().y;
        ret.z = controls.back().z;
        return ret;
    }

    int N = controls.size();

    float den = 0;
    int M = N + 3;


    for(int i = 1; i <= N; i++){
        //int i = 1; // 1.. N-2

        ret.x = ret.x + nCoef(i-1, 3, t, M)*controls[i-1].w*controls[i-1].x;

        ret.y = ret.y + nCoef(i-1, 3, t, M)*controls[i-1].w*controls[i-1].y;

        ret.z = ret.z + nCoef(i-1, 3, t, M)*controls[i-1].w*controls[i-1].z;

        den = den + nCoef(i-1, 3, t, M)*controls[i-1].w;


    }


    if(den == 0){
        ret.x = 0;
        ret.y = 0;
        ret.z = 0;
    }
    else{
        ret.x = ret.x/den;
        ret.y = ret.y/den;
        ret.z = ret.z/den;
    }

    return ret;
}

