#include "SurfaceCoons.h"
using namespace app;

SurfaceCoons::SurfaceCoons(int p_lineStroke, ofColor p_lineColor, ofColor p_lineColorSelected,
                                   double p_tesselation, vector<ofVec4f> p_controls,
                                   ofColor p_colorFill): Shape3D(p_lineStroke, p_lineColor, p_lineColorSelected,
                                                                 p_colorFill){

    m_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    m_mesh.enableColors();
    m_shaderMode = ShaderMode::NONE;
    m_controls = p_controls;
    m_type = EnumVectorDrawMode::PRIMITIVE_SURFACE_COONS;
    m_tesselation = p_tesselation;
    m_colorCourbe = p_colorFill;
    buildMesh();
}

vector<ofVec4f> SurfaceCoons::getControlsPoints(){
    return m_controls;
}

void SurfaceCoons::setTesselation(double p_tesselation){
    m_tesselation = p_tesselation;
    int temp_nivDetail;
    if(0 <= m_tesselation && m_tesselation < 33){
        temp_nivDetail = 3;
    }
    else if(33 <= m_tesselation && m_tesselation < 66){
        temp_nivDetail = 4;
    }
    else if(66 <= m_tesselation && m_tesselation <= 100){
        temp_nivDetail = 5;
    }

    if(m_nivDetail != temp_nivDetail){
        m_mesh.clear();
        buildMesh();
    }
}

void SurfaceCoons::buildMesh(){

    vector<ofVec4f> controls;
    vector<ofVec4f> controls2;
    vector<ofVec4f> controls3;
    vector<ofVec4f> controls4;

    controls.push_back(m_controls[0]);
    controls.push_back(m_controls[1]);
    controls.push_back(m_controls[2]);
    controls.push_back(m_controls[3]);

    controls2.push_back(m_controls[9]);
    controls2.push_back(m_controls[8]);
    controls2.push_back(m_controls[7]);
    controls2.push_back(m_controls[6]);

    controls3.push_back(m_controls[0]);
    controls3.push_back(m_controls[11]);
    controls3.push_back(m_controls[10]);
    controls3.push_back(m_controls[9]);

    controls4.push_back(m_controls[3]);
    controls4.push_back(m_controls[4]);
    controls4.push_back(m_controls[5]);
    controls4.push_back(m_controls[6]);

    int nivDetail;
    if(0 <= m_tesselation && m_tesselation < 33){
        nivDetail = 3;
    }

    else if(33 <= m_tesselation && m_tesselation < 66){
        nivDetail = 4;

    }
    else{
        nivDetail = 5;

    }




    int nSteps = 10;
    ofVec3f ret;

    for(int i = 1; i < nSteps; i++){
        float time1 = (float)i / (float)(nSteps - 1);  // time between 0 and 1
        for(int j = 1; j < nSteps; j++){
            float time2 = (float)j / (float)(nSteps - 1);


            ofVec3f pt1 = surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1));
            ofVec3f pt2 = surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2);
            ofVec3f pt3 = surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1));

            ofVec3f pt4 = pt2;
            ofVec3f pt5 = pt3;
            ofVec3f pt6 = surfaceCoons(controls, controls2, controls3, controls4, time1, time2);

            m_at.push_back(app::ArretTriangle(pt1, pt2, pt3, pt4, pt5,
                                                          pt6, pt2, pt3));

            ofVec3f normal1;
            ofVec3f normal2;
            ofVec3f normal3;
            ofVec3f normal4;
            ofVec3f normal5;
            ofVec3f normal6;

            if(i == 1 && j == 1){
                normal1 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal1.normalize();

                normal2 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal2.normalize();

                normal3 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal3.normalize();

                normal4 = normal2;
                normal5 = normal3;

                normal6 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1)));
                normal6.normalize();

            }

            else if(i == 1 && j > 1){

                normal1 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal1.normalize();

                normal2 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal2.normalize();

                normal3 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal3.normalize();

                normal4 = normal2;
                normal5 = normal3;

                normal6 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1)));
                normal6.normalize();

            }

            else if(i > 1 && j == 1){
                normal1 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal1.normalize();

                normal2 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal2.normalize();

                normal3 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal3.normalize();

                normal4 = normal2;
                normal5 = normal3;

                normal6 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1)));
                normal6.normalize();

            }
            else if((i == nSteps - 1) && (j == nSteps - 1)){

                normal1 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal1.normalize();

                normal2 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal2.normalize();

                normal3 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal3.normalize();

                normal4 = normal2;
                normal5 = normal3;

                normal6 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1)));
                normal6.normalize();

            }

            else if((i == nSteps - 1) && (j < nSteps - 1)){
                normal1 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal1.normalize();

                normal2 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal2.normalize();

                normal3 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal3.normalize();

                normal4 = normal2;
                normal5 = normal3;

                normal6 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1)));
                normal6.normalize();
            }
            else if((i < nSteps - 1) && (j == nSteps - 1)){
                normal1 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal1.normalize();

                normal2 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal2.normalize();

                normal3 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal3.normalize();

                normal4 = normal2;
                normal5 = normal3;

                normal6 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1)));
                normal6.normalize();
            }

            else{

                normal1 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal1.normalize();

                normal2 = (surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)2/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1)));
                normal2.normalize();

                normal3 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1))).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2)
                            -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)2/(float)(nSteps - 1)));
                normal3.normalize();

                normal4 = normal2;
                normal5 = normal3;

                normal6 = (surfaceCoons(controls, controls2, controls3, controls4, time1+(float)1/(float)(nSteps - 1), time2)
                                   -surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2)).cross(
                            surfaceCoons(controls, controls2, controls3, controls4, time1, time2+(float)1/(float)(nSteps - 1))
                            -surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1)));
                normal6.normalize();
            }


            m_mesh.addVertex(pt1);
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255,(float)m_colorCourbe.g/(float)255,(float)m_colorCourbe.b/(float)255));
            m_mesh.addNormal(normal1);
            m_mesh.addVertex(pt2);
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255,(float)m_colorCourbe.g/(float)255,(float)m_colorCourbe.b/(float)255));
            m_mesh.addNormal(normal2);
            m_mesh.addVertex(pt3);
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255,(float)m_colorCourbe.g/(float)255,(float)m_colorCourbe.b/(float)255));
            m_mesh.addNormal(normal3);
            int nbVertex = m_mesh.getNumVertices();
            m_mesh.addIndex(nbVertex - 3);
            m_mesh.addIndex(nbVertex - 2);
            m_mesh.addIndex(nbVertex - 1);

            m_mesh.addVertex(pt4);
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255,(float)m_colorCourbe.g/(float)255,(float)m_colorCourbe.b/(float)255));
            m_mesh.addNormal(normal4);
            m_mesh.addVertex(pt5);
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255,(float)m_colorCourbe.g/(float)255,(float)m_colorCourbe.b/(float)255));
            m_mesh.addNormal(normal5);
            m_mesh.addVertex(pt6);
            m_mesh.addColor(ofFloatColor((float)m_colorCourbe.r/(float)255,(float)m_colorCourbe.g/(float)255,(float)m_colorCourbe.b/(float)255));
            m_mesh.addNormal(normal6);
            nbVertex = m_mesh.getNumVertices();
            m_mesh.addIndex(nbVertex - 3);
            m_mesh.addIndex(nbVertex - 2);
            m_mesh.addIndex(nbVertex - 1);

        }
    }


    if(nivDetail == 4 && m_mesh4.getNumVertices() == 0){


        m_mesh4 = surfaceTesselation4(m_mesh);
    }
    else if(nivDetail == 5 && m_mesh5.getNumVertices() == 0){
        m_mesh4 = surfaceTesselation4(m_mesh);
        m_mesh5 = surfaceTesselation5(m_mesh4);

    }
    m_nivDetail = nivDetail;
}

void SurfaceCoons::draw(){
    if(m_nivDetail == 3){
        m_mesh.drawWireframe();
    }

    else if(m_nivDetail == 4) {
        m_mesh4.drawWireframe();
    }

    else if(m_nivDetail == 5){
        m_mesh5.drawWireframe();
    }
}

ofColor SurfaceCoons::getColorCurve(){
    return m_colorCourbe;

}
void SurfaceCoons::setColorCurve(ofColor p_color){
    m_colorCourbe = p_color;
    m_mesh.clear();
    buildMesh();

}

int SurfaceCoons::fact(int a){
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

ofVec3f SurfaceCoons::surfaceCoons(vector<ofVec4f> controls, vector<ofVec4f> controls2,
                                   vector<ofVec4f> controls3, vector<ofVec4f> controls4, float t1, float t2){
    ofVec3f ret;
    ofVec3f lerpU;
    ofVec3f lerpV;
    ofVec3f blerp;

    ret.x = 0;
    ret.y = 0;
    ret.z = 0;

    lerpU.x = (1-t2)*CourbeNurbs::nurbs(controls, t1).x + t2*CourbeNurbs::nurbs(controls2, t1).x;

    lerpV.x = (1-t1)*CourbeNurbs::nurbs(controls3, t2).x + t1*CourbeNurbs::nurbs(controls4, t2).x;

    blerp.x = (1-t1)*(1-t2)*CourbeNurbs::nurbs(controls, 0).x + t1*(1-t2)*CourbeNurbs::nurbs(controls, 1).x
            + (1-t1)*t2*CourbeNurbs::nurbs(controls2, 0).x + t1*t2*CourbeNurbs::nurbs(controls2, 1).x;


    lerpU.y = (1-t2)*CourbeNurbs::nurbs(controls, t1).y + t2*CourbeNurbs::nurbs(controls2, t1).y;

    lerpV.y = (1-t1)*CourbeNurbs::nurbs(controls3, t2).y + t1*CourbeNurbs::nurbs(controls4, t2).y;

    blerp.y = (1-t1)*(1-t2)*CourbeNurbs::nurbs(controls, 0).y + t1*(1-t2)*CourbeNurbs::nurbs(controls, 1).y
            + (1-t1)*t2*CourbeNurbs::nurbs(controls2, 0).y + t1*t2*CourbeNurbs::nurbs(controls2, 1).y;

    lerpU.z = (1-t2)*CourbeNurbs::nurbs(controls, t1).z + t2*CourbeNurbs::nurbs(controls2, t1).z;

    lerpV.z = (1-t1)*CourbeNurbs::nurbs(controls3, t2).z + t1*CourbeNurbs::nurbs(controls4, t2).z;

    blerp.z = (1-t1)*(1-t2)*CourbeNurbs::nurbs(controls, 0).z + t1*(1-t2)*CourbeNurbs::nurbs(controls, 1).z
            + (1-t1)*t2*CourbeNurbs::nurbs(controls2, 0).z + t1*t2*CourbeNurbs::nurbs(controls2, 1).z;


    ret.x = lerpU.x + lerpV.x - blerp.x;
    ret.y = lerpU.y + lerpV.y - blerp.y;
    ret.z = lerpU.z + lerpV.z - blerp.z;

    return ret;
}

ofMesh SurfaceCoons::surfaceTesselation4(const ofMesh &mesh){
        // pour chaque poly, ajouter sommet central
        vector<ofVec3f> tempVector;
        ofMesh meshret;
        meshret.setMode(OF_PRIMITIVE_LINES);
        vector<ofVec3f> vectorPts;
        vector<ofVec3f> vectorNormalPts;
        vector<ofVec3f> vectorSommetsArrets;
        vector<ofVec3f> vectorNormalSommetsArrets;

        int N = mesh.getVertices().size()/3;
    for(int i = 0; i < N; i++){

        vectorPts.push_back(mesh.getVertex(3*i));
        vectorNormalPts.push_back(mesh.getNormal(3*i));
        vectorPts.push_back(mesh.getVertex(3*i+1));
        vectorNormalPts.push_back(mesh.getNormal(3*i+1));
        vectorPts.push_back(mesh.getVertex(3*i+2));
        vectorNormalPts.push_back(mesh.getNormal(3*i+2));

        ofVec3f sommetCentral = vectorPts[0]/3 + vectorPts[1]/3 + vectorPts[2]/3;
        ofVec3f normalCentral = vectorNormalPts[0]/3 + vectorNormalPts[1]/3 + vectorNormalPts[2]/3;

        // pour chaque arret, ajouter sommet
        // trouver triangle adjacent (fct)

        tempVector.clear();
        tempVector = ArretTriangle::get2Triangles(m_at, vectorPts[0], vectorPts[1]);
        if(tempVector.size() == 6){
            vectorSommetsArrets.push_back(vectorPts[0]/4 + vectorPts[1]/4 +
                    (tempVector[0]/3 + tempVector[1]/3 + tempVector[2]/3)/4 +
                    (tempVector[3]/3 + tempVector[4]/3 + tempVector[5]/3)/4);
        }
        else{
            vectorSommetsArrets.push_back(vectorPts[0]/2 + vectorPts[1]/2);
        }

        vectorNormalSommetsArrets.push_back(vectorNormalPts[0]/2 + vectorNormalPts[1]/2);
        tempVector.clear();
        tempVector = app::ArretTriangle::get2Triangles(m_at, vectorPts[1], vectorPts[2]);
        if(tempVector.size() == 6){
            vectorSommetsArrets.push_back(vectorPts[1]/4 + vectorPts[2]/4 +
                    (tempVector[0]/3 + tempVector[1]/3 + tempVector[2]/3)/4 +
                    (tempVector[3]/3 + tempVector[4]/3 + tempVector[5]/3)/4);
        }
        else{
            vectorSommetsArrets.push_back(vectorPts[1]/2 + vectorPts[2]/2);
        }
        vectorNormalSommetsArrets.push_back(vectorNormalPts[1]/2 + vectorNormalPts[2]/2);
        tempVector.clear();
        tempVector = app::ArretTriangle::get2Triangles(m_at, vectorPts[2], vectorPts[0]);
        if(tempVector.size() == 6){
            vectorSommetsArrets.push_back(vectorPts[2]/4 + vectorPts[0]/4+
                    (tempVector[0]/3 + tempVector[1]/3 + tempVector[2]/3)/4 +
                    (tempVector[3]/3 + tempVector[4]/3 + tempVector[5]/3)/4);
        }
        else{
            vectorSommetsArrets.push_back(vectorPts[2]/2 + vectorPts[0]/2);
        }
        vectorNormalSommetsArrets.push_back(vectorNormalPts[2]/2 + vectorNormalPts[0]/2);

        // pour chaque arret, ajouter arret
        // central-arret

        for(int j = 0; j < 3; j++){
            meshret.addVertex(sommetCentral);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(normalCentral);

            meshret.addVertex(vectorSommetsArrets[j]);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(vectorNormalSommetsArrets[j]);

            meshret.addVertex(vectorSommetsArrets[j]);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(vectorNormalSommetsArrets[j]);
            int l = j + 1;
            if(j == 2){
                l = 0;
            }

            meshret.addVertex(vectorPts[l]);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(vectorNormalPts[l]);

            meshret.addVertex(vectorPts[l]);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(vectorNormalPts[l]);
            int k = j + 1;
            if(j == 2){
                k = 0;
            }


            meshret.addVertex(vectorSommetsArrets[k]);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(vectorNormalSommetsArrets[k]);

            meshret.addVertex(vectorSommetsArrets[k]);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(vectorNormalSommetsArrets[k]);

            meshret.addVertex(sommetCentral);
            meshret.addColor(ofFloatColor(1, 0, 1));
            meshret.addNormal(normalCentral);


        }

        vectorPts.clear();
        vectorSommetsArrets.clear();
        vectorNormalPts.clear();
        vectorNormalSommetsArrets.clear();
    }

    return meshret;

}


ofMesh SurfaceCoons::surfaceTesselation5(const ofMesh &mesh){
        // pour chaque poly, ajouter sommet central
        ofMesh meshret;
        meshret.setMode(OF_PRIMITIVE_LINES);
        vector<ofVec3f> vectorPts;
        vector<ofVec3f> vectorNormalPts;
        vector<ofVec3f> vectorSommetsArrets;
        vector<ofVec3f> vectorNormalSommetsArrets;

        int N = mesh.getVertices().size()/8;
    for(int i = 0; i < N; i++){

        vectorPts.push_back(mesh.getVertex(8*i));
        vectorNormalPts.push_back(mesh.getNormal(8*i));
        vectorPts.push_back(mesh.getVertex(8*i+2));
        vectorNormalPts.push_back(mesh.getNormal(8*i+2));
        vectorPts.push_back(mesh.getVertex(8*i+4));
        vectorNormalPts.push_back(mesh.getNormal(8*i+4));
        vectorPts.push_back(mesh.getVertex(8*i+6));
        vectorNormalPts.push_back(mesh.getNormal(8*i+6));

        ofVec3f sommetCentral = vectorPts[0]/4 + vectorPts[1]/4 + vectorPts[2]/4 + vectorPts[3]/4;
        ofVec3f normalCentral = vectorNormalPts[0]/4 + vectorNormalPts[1]/4 + vectorNormalPts[2]/4 + vectorNormalPts[3]/4;

        // pour chaque arret, ajouter sommet
        // trouver triangle adjacent (fct)

        vectorSommetsArrets.push_back(vectorPts[0]/2 + vectorPts[1]/2);
        vectorNormalSommetsArrets.push_back(vectorNormalPts[0]/2 + vectorNormalPts[1]/2);
        vectorSommetsArrets.push_back(vectorPts[1]/2 + vectorPts[2]/2);
        vectorNormalSommetsArrets.push_back(vectorNormalPts[1]/2 + vectorNormalPts[2]/2);
        vectorSommetsArrets.push_back(vectorPts[2]/2 + vectorPts[3]/2);
        vectorNormalSommetsArrets.push_back(vectorNormalPts[2]/2 + vectorNormalPts[3]/2);
        vectorSommetsArrets.push_back(vectorPts[3]/2 + vectorPts[0]/2);
        vectorNormalSommetsArrets.push_back(vectorNormalPts[3]/2 + vectorNormalPts[0]/2);

        // pour chaque arret, ajouter arret
        // central-arret

        for(int j = 0; j < 4; j++){
            meshret.addVertex(sommetCentral);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(normalCentral);

            meshret.addVertex(vectorSommetsArrets[j]);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(vectorNormalSommetsArrets[j]);

            meshret.addVertex(vectorSommetsArrets[j]);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(vectorNormalSommetsArrets[j]);
            int l = j + 1;
            if(j == 3){
                l = 0;
            }

            meshret.addVertex(vectorPts[l]);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(vectorNormalPts[l]);

            meshret.addVertex(vectorPts[l]);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(vectorNormalPts[l]);
            int k = j + 1;
            if(j == 3){
                k = 0;
            }


            meshret.addVertex(vectorSommetsArrets[k]);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(vectorNormalSommetsArrets[k]);

            meshret.addVertex(vectorSommetsArrets[k]);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(vectorNormalSommetsArrets[k]);

            meshret.addVertex(sommetCentral);
            meshret.addColor(ofFloatColor(1, 1, 0));
            meshret.addNormal(normalCentral);


        }

        vectorPts.clear();
        vectorSommetsArrets.clear();
        vectorNormalPts.clear();
        vectorNormalSommetsArrets.clear();
    }

    return meshret;

}

SurfaceCoons::~SurfaceCoons(){

}
