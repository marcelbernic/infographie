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
    m_mesh.clear();
    buildMesh();
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

    controls2.push_back(m_controls[3]);
    controls2.push_back(m_controls[4]);
    controls2.push_back(m_controls[5]);
    controls2.push_back(m_controls[6]);

    controls3.push_back(m_controls[6]);
    controls3.push_back(m_controls[7]);
    controls3.push_back(m_controls[8]);
    controls3.push_back(m_controls[9]);

    controls4.push_back(m_controls[9]);
    controls4.push_back(m_controls[10]);
    controls4.push_back(m_controls[11]);
    controls4.push_back(m_controls[0]);


    int nSteps = 50;
    ofVec3f ret;

    for(int i = 0; i < nSteps; i++){
        float time1 = (float)i / (float)(nSteps - 1);  // time between 0 and 1
        for(int j = 0; j < nSteps; j++){
            float time2 = (float)j / (float)(nSteps - 1);


            ofVec3f pt1 = surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2-(float)1/(float)(nSteps - 1));
            ofVec3f pt2 = surfaceCoons(controls, controls2, controls3, controls4, time1-(float)1/(float)(nSteps - 1), time2);
            ofVec3f pt3 = surfaceCoons(controls, controls2, controls3, controls4, time1, time2-(float)1/(float)(nSteps - 1));

            ofVec3f pt4 = pt2;
            ofVec3f pt5 = pt3;
            ofVec3f pt6 = surfaceCoons(controls, controls2, controls3, controls4, time1, time2);

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


}

void SurfaceCoons::draw(){
    m_mesh.draw();

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
