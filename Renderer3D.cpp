#include "Renderer3D.h"
#include "ofxCubeMap.h"
static float minBrightness = 1;

Renderer3D::Renderer3D()
{
}


Renderer3D::~Renderer3D()
{
}

void Renderer3D::setup(const string p_name, ofApp *p_app) {
    ofSetFrameRate(60);

    m_app = p_app;

    //Default values:
    x.set("Position x", 0, 0, 1024);
    y.set("Position y", 0, 0, 768);
    z.set("Position z", 0, -300, 300);

    rotx.set("Rotate axe x", 0, 0.0, 360);
    roty.set("Rotate axe y", 0, 0.0, 360);
    rotz.set("Rotate axe z", 0, 0.0, 360);

    dimension.set("Dimension", 40, 0, 300);
    tesselation.set("Tesselation", 5, 0, 100);

    bCloud.set("Cloud Points", false);

    parameters3D.setName(p_name + " settings");
    parameters3D.add(bCloud);
    parameters3D.add(x);
    parameters3D.add(y);
    parameters3D.add(z);

    parameters3D.add(rotx);
    parameters3D.add(roty);
    parameters3D.add(rotz);
    parameters3D.add(dimension);
    parameters3D.add(tesselation);

    cameraSettings.setName("Camera Settings");

    x.addListener(this, &Renderer3D::xChanged);
    y.addListener(this, &Renderer3D::yChanged);
    z.addListener(this, &Renderer3D::zChanged);

    rotx.addListener(this, &Renderer3D::rotxChanged);
    roty.addListener(this, &Renderer3D::rotyChanged);
    rotz.addListener(this, &Renderer3D::rotzChanged);
    dimension.addListener(this, &Renderer3D::dimensionChanged);
    tesselation.addListener(this, &Renderer3D::tesselationChanged);
    fov.addListener(this, &Renderer3D::fovChanged);
    aspectRatio.addListener(this, &Renderer3D::aspectRatioChanged);
    nearClip.addListener(this, &Renderer3D::nearClipChanged);
    farClip.addListener(this, &Renderer3D::farClipChanged);

    bCloud.addListener(this, &Renderer3D::bCloudChanged);

    m_lights.push_back(new ofLight());


    for (ofLight* o : m_lights){
        o->setPointLight();
        o->setPosition(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
        o->enable();
    }
    m_camSelection = 0;

    cam.push_back(ofCamera());
    cam[m_camSelection].resetTransform();
    cam[m_camSelection].setFov(60);
    cam[m_camSelection].clearParent();

    cam[m_camSelection].setPosition(ofGetWidth()/2, ofGetHeight()/2, 1000);
    cam[m_camSelection].lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, -1));

	ofImage heightmap;
	heightmap.loadImage("image.jpg");
	for (int y = 0; y < heightmap.getHeight(); y++) {
		for (int x = 0; x < heightmap.getWidth(); x++) {
			minBrightness = std::min(minBrightness, float((heightmap.getColor(x, y).r / 255.0) * 0.3 + (heightmap.getColor(x, y).g / 255.0) * 0.59 + (heightmap.getColor(x, y).b / 255.0) * 0.11));
		}
	}


    fov.set("Camera Fov", cam[m_camSelection].getFov(), 0, 180);
    aspectRatio.set("Aspect Ratio", cam[m_camSelection].getAspectRatio(), 0, 5);
    nearClip.set("Near Clip Distance", cam[m_camSelection].getNearClip(), 0, 100);
    farClip.set("Far Clip Distance", cam[m_camSelection].getFarClip(),  0, 100);
    cameraSettings.add(fov);
    cameraSettings.add(aspectRatio);
    cameraSettings.add(nearClip);
    cameraSettings.add(farClip);
}

void Renderer3D::draw() {


    ofBackgroundGradient(ofColor::white, ofColor::gray);
    ofEnableDepthTest();

    ofEnableLighting();

    if(AppState::CAMERA == m_app->m_state){
        for(int i = 0; i < cam.size(); i++){
            if(i == m_camSelection){
                cam[i].begin();
            }
        }
        ofPushMatrix();
        ofScale(1, -1, 1);
        ofTranslate(0, -ofGetHeight(), 0);
    }

    if (!m_app->isTakingScreenshot) {
        switch (m_app->m_state) {
        case AppState::BUILD_CUBE:
            if (m_app->m_buffer3D.size() == 1) {
                m_app->m_obj3DVector[m_app->m_obj3DVector.size() - 1]->draw();
            }
            break;
        case AppState::BUILD_SPHERE:
            if (m_app->m_buffer3D.size() == 1) {
                m_app->m_obj3DVector[m_app->m_obj3DVector.size() - 1]->draw();
            }
            break;
        }
    }
    for (Obj3D* o : m_app->m_obj3DVector) {
        switch (o->getType()) {
        case EnumVectorDrawMode::PRIMITIVE_CUBE: {
            app::Cube3D* c = dynamic_cast<app::Cube3D*>(o);
            drawCube3D(c);
        }
            break;
        case EnumVectorDrawMode::PRIMITIVE_SPHERE: {
            app::Sphere3D* c = dynamic_cast<app::Sphere3D*>(o);
            drawSphere3D(c);
        }
            break;

		case EnumVectorDrawMode::PRIMITIVE_TERRAIN: {
			app::Terrain3D* c = dynamic_cast<app::Terrain3D*>(o);
			drawTerrain3D(c);
		}
			break;
        case EnumVectorDrawMode::PRIMITIVE_COURBE_CATMULLROM: {
                    app::CourbeCatmullRom* c = dynamic_cast<app::CourbeCatmullRom*>(o);
                    drawCourbeCatmullRom(c);
                }
            break;
        case EnumVectorDrawMode::PRIMITIVE_COURBE_NURBS: {
            app::CourbeNurbs* c = dynamic_cast<app::CourbeNurbs*>(o);
            drawCourbeNurbs(c);
        }
            break;
        case EnumVectorDrawMode::PRIMITIVE_COURBE_BEZIERCUBIQUE: {
            app::CourbeBezierCubique* c = dynamic_cast<app::CourbeBezierCubique*>(o);
            drawCourbeBezierCubique(c);
        }
            break;
        case EnumVectorDrawMode::PRIMITIVE_SURFACE_BEZIERCUBIQUE: {
            app::SurfaceBezierCubique* c = dynamic_cast<app::SurfaceBezierCubique*>(o);
            drawSurfaceBezierCubique(c);
        }
            break;
        case EnumVectorDrawMode::PRIMITIVE_SURFACE_COONS: {
            app::SurfaceCoons* c = dynamic_cast<app::SurfaceCoons*>(o);
            drawSurfaceCoons(c);
        }
            break;
        }

    }

    if(AppState::CAMERA == m_app->m_state){
    ofPopMatrix();
    for(int i = 0; i < cam.size(); i++){
        if(m_camSelection == i){
            cam[i].end();
        }
    }
    }

    ofDisableLighting();
    ofDisableDepthTest();

}



void Renderer3D::xChanged(int & p_x) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setPositionX(p_x);
                }
                break;
            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setPositionX(p_x);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setPositionX(p_x);
				}
			break;
            }
        }
    }
}
void Renderer3D::yChanged(int & p_y) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setPositionY(p_y);
                }
                break;
            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setPositionY(p_y);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setPositionY(p_y);
				}
				break;
            }
        }
    }
}
void Renderer3D::zChanged(int & p_z) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setPositionZ(p_z);
                }
                break;

            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setPositionZ(p_z);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setPositionZ(p_z);
				}
				break;

            }
        }
    }
}

void Renderer3D::rotxChanged(double & p_rotx) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setRotateX(p_rotx);
                }
                break;
            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setRotateX(p_rotx);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setRotateX(p_rotx);
				}
				break;
            }
        }
    }
}

void Renderer3D::rotyChanged(double & p_roty) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setRotateY(p_roty);
                }
                break;
            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setRotateY(p_roty);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setRotateY(p_roty);
				}
				break;
            }
        }
    }
}

void Renderer3D::rotzChanged(double & p_rotz) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setRotateZ(p_rotz);
                }
                break;
            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setRotateZ(p_rotz);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setRotateZ(p_rotz);
				}
				break;
            }
        }
    }
}

void Renderer3D::bCloudChanged(bool &p_cloud){
    bCloud.set(p_cloud);
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setCloud(p_cloud);
                }
                break;
            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setCloud(p_cloud);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setCloud(p_cloud);
				}
				break;
            }
        }
    }
  }

void Renderer3D::dimensionChanged(double & p_dimension){
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_CUBE:{
                app::Cube3D *ptr_cube;
                ptr_cube = dynamic_cast<app::Cube3D*>(o);
                ptr_cube->setDimension(p_dimension);
                }
                break;
            case PRIMITIVE_SPHERE:{
                app::Sphere3D *ptr_sphere;
                ptr_sphere = dynamic_cast<app::Sphere3D*>(o);
                ptr_sphere->setDimension(p_dimension);
                }
                break;
			case PRIMITIVE_TERRAIN: {
				app::Terrain3D *ptr_terrain;
				ptr_terrain = dynamic_cast<app::Terrain3D*>(o);
				ptr_terrain->setDimension(p_dimension);
				}
				break;
            }
        }
    }
}

void Renderer3D::tesselationChanged(double & p_tesselation){
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            switch (o->getType()) {
            case PRIMITIVE_COURBE_CATMULLROM:{
                app::CourbeCatmullRom *ptr_courbe;
                ptr_courbe = dynamic_cast<app::CourbeCatmullRom*>(o);
                ptr_courbe->setTesselation(p_tesselation);
                }
                break;
            case PRIMITIVE_COURBE_NURBS:{
                app::CourbeNurbs *ptr_courbe;
                ptr_courbe = dynamic_cast<app::CourbeNurbs*>(o);
                ptr_courbe->setTesselation(p_tesselation);
                }
                break;
            case PRIMITIVE_COURBE_BEZIERCUBIQUE:{
                app::CourbeBezierCubique *ptr_courbe;
                ptr_courbe = dynamic_cast<app::CourbeBezierCubique*>(o);
                ptr_courbe->setTesselation(p_tesselation);
                }
                break;
            case PRIMITIVE_SURFACE_BEZIERCUBIQUE:{
                app::SurfaceBezierCubique *ptr_courbe;
                ptr_courbe = dynamic_cast<app::SurfaceBezierCubique*>(o);
                ptr_courbe->setTesselation(p_tesselation);
                }
                break;
            case PRIMITIVE_SURFACE_COONS:{
                app::SurfaceCoons *ptr_courbe;
                ptr_courbe = dynamic_cast<app::SurfaceCoons*>(o);
                ptr_courbe->setTesselation(p_tesselation);
                }
                break;

            }
        }
    }
}

void Renderer3D::fovChanged(double & p_fov){

    cam[m_camSelection].setFov(p_fov);
}

void Renderer3D::aspectRatioChanged(double & p_aspectRatio){

    cam[m_camSelection].setAspectRatio(p_aspectRatio);
}

void Renderer3D::nearClipChanged(double & p_nearClip){

    cam[m_camSelection].setNearClip(p_nearClip);
}

void Renderer3D::farClipChanged(double & p_farClip){

    cam[m_camSelection].setFarClip(p_farClip);
}

void Renderer3D::imageExport(const string path, const string extension) const
{
    ofImage imageTemp;
    string fileName = path + "." + extension;



    imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    imageTemp.save(fileName);

    ofLog() << "<export image: " << fileName << ">";
}

void Renderer3D::drawCube3D(app::Cube3D *p_cube) {
	ofShader shader;
	ofImage colormap, heightmap;
	ofxCubeMap myCubeMap = ofxCubeMap();
	int selected = 0;
    if (p_cube->isSelected()) {
        p_cube->setColorCube(m_app->renderer2d->colorSelected);
        ofSetColor(m_app->renderer2d->colorSelected);
		selected = 1;
    }
    else{
        p_cube->setColorCube(p_cube->getColorFill());
        ofSetColor(p_cube->getColorFill());
    }
	switch (p_cube->m_shaderMode) {
	case DISPLACEMENT:
		ofDisableArbTex();


		colormap.loadImage("image.jpg");
		heightmap.loadImage("image.jpg");
		shader.load("shaders/heightmap");

		shader.begin();
		shader.setUniformTexture("colormap", colormap, 0);
		shader.setUniformTexture("bumpmap", heightmap, 1);
		shader.setUniform1i("selected", selected);
		shader.setUniform1i("maxHeight", 20);
		shader.setUniform1f("min", minBrightness);
		p_cube->draw();
		shader.end();
		ofEnableArbTex();

		break;
	case CUBE:
		shader.load("shaders/CubeMap");
		myCubeMap.loadImages("right.jpeg",
			"left.jpeg",
			"base.jpeg",
			"top.jpeg",
			"front.jpeg",
			"back.jpeg");

		myCubeMap.bind();
		shader.begin();

		shader.setUniform1i("EnvMap", 0);
		shader.setUniform1f("reflectivity", 0.8);
		shader.setUniform1i("selected", selected);

		p_cube->draw();

		shader.end();
		myCubeMap.unbind();
	case NONE:
		p_cube->draw();
		break;
	}
}

void Renderer3D::drawSphere3D(app::Sphere3D *p_sphere) {
	ofShader shader;
	ofImage colormap, heightmap;
	ofxCubeMap myCubeMap = ofxCubeMap();
	int selected = 0;
    if (p_sphere->isSelected()) {
        p_sphere->setColorSphere(m_app->renderer2d->colorSelected);
		selected = 1;
    }
    else{
        p_sphere->setColorSphere(p_sphere->getColorFill());
    }
	switch (p_sphere->m_shaderMode) {
	case DISPLACEMENT:
		ofDisableArbTex();
		

		colormap.loadImage("image.jpg");
		heightmap.loadImage("image.jpg");
		shader.load("shaders/heightmap");

		shader.begin();
		shader.setUniformTexture("colormap", colormap, 0);
		shader.setUniformTexture("bumpmap", heightmap, 1);
		shader.setUniform1i("selected", selected);
		shader.setUniform1i("maxHeight", 20);
		shader.setUniform1f("min", minBrightness);
		p_sphere->draw();
		shader.end();
		ofEnableArbTex();

		break;
	case CUBE:
		shader.load("shaders/CubeMap");
		myCubeMap.loadImages("right.jpeg",
			"left.jpeg",
			"base.jpeg",
			"top.jpeg",
			"front.jpeg",
			"back.jpeg");

		myCubeMap.bind();
		shader.begin();
		shader.setUniform1i("EnvMap", 0);
		shader.setUniform1f("reflectivity", 0.8);
		shader.setUniform1i("selected", selected);
		
		p_sphere->draw();
		shader.end();
		myCubeMap.unbind();
	case NONE:
		p_sphere->draw();
		break;
	}	
}

void Renderer3D::drawTerrain3D(app::Terrain3D *p_terrain) {
	

	//ofEasyCam easyCam;
	if (p_terrain->isSelected()) {
		ofSetColor(255, 255, 255);
	}
	else {
		ofSetColor(128, 128, 128);
	}
	//ofRotateX(p_terrain->m_primitive.getOrientationQuat().x()*360);
	ofTranslate(p_terrain->getPosition().x, p_terrain->getPosition().y, p_terrain->getPosition().z);
	
	p_terrain->m_mesh.drawWireframe();
	
	//cout << p_terrain->m_primitive.getOrientationQuat().x()*360 << endl;
	ofTranslate(-p_terrain->getPosition().x, -p_terrain->getPosition().y, -p_terrain->getPosition().z);
	//ofRotateX(-p_terrain->m_primitive.getOrientationQuat().x());

	//easyCam.end();
}

bool Renderer3D::notIncluded(Obj3D* p_obj3d){
    bool ret = true;
    for(int i = 0; i < m_controls.size(); i++){
        if(p_obj3d->getType() == EnumVectorDrawMode::PRIMITIVE_CUBE){
            app::Cube3D* c = dynamic_cast<app::Cube3D*>(p_obj3d);
            if(c->getPosition().x == m_controls[i].x && c->getPosition().y == m_controls[i].y
                    && c->getPosition().z == m_controls[i].z){
                ret = false;
                break;
            }

        }
        if(p_obj3d->getType() == EnumVectorDrawMode::PRIMITIVE_SPHERE){
            app::Sphere3D* c = dynamic_cast<app::Sphere3D*>(p_obj3d);
            if(c->getPosition().x == m_controls[i].x && c->getPosition().y == m_controls[i].y
                    && c->getPosition().z == m_controls[i].z){
                ret = false;
                break;
            }

        }
    }

    return ret;
}

void Renderer3D::drawCourbeCatmullRom(app::CourbeCatmullRom *p_courbeCatmullRom) {
    int selected = 0;
    if (p_courbeCatmullRom->isSelected()) {
        p_courbeCatmullRom->setColorCurve(m_app->renderer2d->colorSelected);
        ofSetColor(m_app->renderer2d->colorSelected);
        selected = 1;
    }
    else{
        p_courbeCatmullRom->setColorCurve(p_courbeCatmullRom->getColorFill());
        ofSetColor(p_courbeCatmullRom->getColorFill());
    }
    p_courbeCatmullRom->draw();
}

void Renderer3D::drawCourbeNurbs(app::CourbeNurbs *p_courbeNurbs) {
    int selected = 0;
    if (p_courbeNurbs->isSelected()) {
        p_courbeNurbs->setColorCurve(m_app->renderer2d->colorSelected);
        ofSetColor(m_app->renderer2d->colorSelected);
        selected = 1;
    }
    else{
        p_courbeNurbs->setColorCurve(p_courbeNurbs->getColorFill());
        ofSetColor(p_courbeNurbs->getColorFill());
    }
    p_courbeNurbs->draw();
}

void Renderer3D::drawCourbeBezierCubique(app::CourbeBezierCubique *p_courbeBezier) {
    int selected = 0;
    if (p_courbeBezier->isSelected()) {
        p_courbeBezier->setColorCurve(m_app->renderer2d->colorSelected);
        ofSetColor(m_app->renderer2d->colorSelected);
        selected = 1;
    }
    else{
        p_courbeBezier->setColorCurve(p_courbeBezier->getColorFill());
        ofSetColor(p_courbeBezier->getColorFill());
    }
    p_courbeBezier->draw();
}

void Renderer3D::drawSurfaceBezierCubique(app::SurfaceBezierCubique *p_surfaceBezier) {
    if (p_surfaceBezier->isSelected()) {
        p_surfaceBezier->setColorCurve(m_app->renderer2d->colorSelected);
        ofSetColor(m_app->renderer2d->colorSelected);
    }
    else{
        p_surfaceBezier->setColorCurve(p_surfaceBezier->getColorFill());
        ofSetColor(p_surfaceBezier->getColorFill());
    }
    p_surfaceBezier->draw();
}

void Renderer3D::drawSurfaceCoons(app::SurfaceCoons *p_surfaceCoons) {
    if (p_surfaceCoons->isSelected()) {
        p_surfaceCoons->setColorCurve(m_app->renderer2d->colorSelected);
        ofSetColor(m_app->renderer2d->colorSelected);
    }
    else{
        p_surfaceCoons->setColorCurve(p_surfaceCoons->getColorFill());
        ofSetColor(p_surfaceCoons->getColorFill());
    }
    p_surfaceCoons->draw();
}


