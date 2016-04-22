#pragma once

#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofApp.h"
#include "Obj3D.h"
#include "Cube3D.h"
#include "Sphere3D.h"
#include "Terrain3D.h"
#include "CourbeCatmullRom.h"
#include "CourbeNurbs.h"
#include "CourbeBezierCubique.h"
#include "SurfaceBezierCubique.h"


//class Renderer3D;
class ofApp;

class Renderer3D
{
private:
    ofApp * m_app;
public:
    Renderer3D();
    ~Renderer3D();

    void setup(const string p_name, ofApp *p_app);

    void draw();

    void imageExport(const string path, const string extension) const;

    void xChanged(int & p_x);
    void yChanged(int & p_y);
    void zChanged(int & p_z);

    void rotxChanged(double & p_rotx);
    void rotyChanged(double & p_roty);
    void rotzChanged(double & p_rotz);
    void dimensionChanged(double & p_dimension);
    void tesselationChanged(double & p_tesselation);

    void bCloudChanged(bool &p_cloud);

    void drawCube3D(app::Cube3D *p_cube);

    void drawSphere3D(app::Sphere3D *p_sphere);

	void drawTerrain3D(app::Terrain3D *p_terrain);

    void drawCourbeCatmullRom(app::CourbeCatmullRom *p_courbeCatmullRom);
    void drawCourbeNurbs(app::CourbeNurbs *p_courbeNurbs);
    void drawCourbeBezierCubique(app::CourbeBezierCubique *p_courbeBezier);
    void drawSurfaceBezierCubique(app::SurfaceBezierCubique *p_surfaceBezier);
    bool notIncluded(Obj3D* p_obj3d);

    ofParameterGroup parameters3D;
    ofParameter<int> x;
    ofParameter<int> y;
    ofParameter<int> z;

    ofParameter<double> rotx;
    ofParameter<double> roty;
    ofParameter<double> rotz;

    ofParameter<double> dimension;
    ofParameter<double> tesselation;

    ofParameter<bool> bCloud;

    std::vector<ofLight*> m_lights;
    std::vector<ofVec4f> m_controls;

    ofCamera cam1;

};
