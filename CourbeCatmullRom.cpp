#include "CourbeCatmullRom.h"
using namespace app;

CourbeCatmullRom::CourbeCatmullRom(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected,
                                   double p_tesselation, vector<ofVec4f> p_controls,
                                   ofColor p_colorFill): Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected,
                                                                 p_colorFill){
    m_mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    m_mesh.enableColors();
    m_shaderMode = ShaderMode::NONE;
    m_controls = p_controls;
    m_type = EnumVectorDrawMode::PRIMITIVE_COURBE_CATMULLROM;
    m_tesselation = p_tesselation;
    m_colorCourbe = p_colorFill;
    buildMesh();
}

vector<ofVec4f> CourbeCatmullRom::getControlsPoints(){
    return m_controls;
}

void CourbeCatmullRom::setTesselation(double p_tesselation){
    m_tesselation = p_tesselation;
    m_mesh.clear();
    buildMesh();
}

void CourbeCatmullRom::buildMesh(){
    ofVec3f ret;

    int nSteps = floor(m_tesselation) + 1;

    //for(int k = 0; k < ){

        for(int i = 0; i < nSteps; i++){
            float time1 = (float)i / (float)(nSteps - 1);  // time between 0 and 1

            int nbPoints = m_controls.size();

            int indexPoint;
            int timeBegin = 0;

            for(int ii = 1; ii <= nbPoints - 3; ii++){
                if((float)ii/(float)(nbPoints-3) > time1){
                    indexPoint = ii;
                    timeBegin = ii - 1;
                    break;

                }
            }

            if(time1 == 1){
                indexPoint = nbPoints - 3;

            }

            float t1, t2, t3;

            t1 = (time1 - (float)timeBegin/(float)(nbPoints - 3))*(float)(nbPoints - 3);

            //t1 = t;
            t2 = t1*t1;
            t3 = t1*t1*t1;
            ofVec3f p1;
            p1.x = m_controls[indexPoint-1].x;
            p1.y = m_controls[indexPoint-1].y;
            p1.z = m_controls[indexPoint-1].z;
            ofVec3f p2;
            p2.x = m_controls[indexPoint].x;
            p2.y = m_controls[indexPoint].y;
            p2.z = m_controls[indexPoint].z;
            ofVec3f p3;
            p3.x = m_controls[indexPoint+1].x;
            p3.y = m_controls[indexPoint+1].y;
            p3.z = m_controls[indexPoint+1].z;
            ofVec3f p4;
            p4.x = m_controls[indexPoint+2].x;
            p4.y = m_controls[indexPoint+2].y;
            p4.z = m_controls[indexPoint+2].z;

            ret.x = (0 - 1*t1 + 2*t2 - t3)*p1.x/2 + (2 + 0*t1 - 5*t2 + 3*t3)*p2.x/2 + (0 + 1*t1 + 4*t2 - 3*t3)*p3.x/2
                    + (0 + 0*t1 - 1*t2 + 1*t3)*p4.x/2;
            ret.y = (0 - 1*t1 + 2*t2 - t3)*p1.y/2 + (2 + 0*t1 - 5*t2 + 3*t3)*p2.y/2 + (0 + 1*t1 + 4*t2 - 3*t3)*p3.y/2
                    + (0 + 0*t1 - 1*t2 + 1*t3)*p4.y/2;
            ret.z = (0 - 1*t1 + 2*t2 - t3)*p1.z/2 + (2 + 0*t1 - 5*t2 + 3*t3)*p2.z/2 + (0 + 1*t1 + 4*t2 - 3*t3)*p3.z/2
                    + (0 + 0*t1 - 1*t2 + 1*t3)*p4.z/2;

            m_mesh.addVertex(ofPoint(ret.x, ret.y, ret.z));
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255, (float)m_colorCourbe.g/(float)255, (float)m_colorCourbe.b/(float)255));  // add a color at that vertex
        }
    //}


}

void CourbeCatmullRom::draw(){
    m_mesh.draw();

}

void CourbeCatmullRom::setColorCurve(ofColor p_color){
    m_colorCourbe = p_color;
    m_mesh.clear();
    buildMesh();

}
