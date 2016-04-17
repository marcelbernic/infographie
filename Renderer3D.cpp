#include "Renderer3D.h"
#include "ofxCubeMap.h"

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

    x.addListener(this, &Renderer3D::xChanged);
    y.addListener(this, &Renderer3D::yChanged);
    z.addListener(this, &Renderer3D::zChanged);

    rotx.addListener(this, &Renderer3D::rotxChanged);
    roty.addListener(this, &Renderer3D::rotyChanged);
    rotz.addListener(this, &Renderer3D::rotzChanged);
    dimension.addListener(this, &Renderer3D::dimensionChanged);

    bCloud.addListener(this, &Renderer3D::bCloudChanged);

    m_lights.push_back(new ofLight());


    for (ofLight* o : m_lights){
        o->setPointLight();
        o->setPosition(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 0));
        o->enable();
    }

    cam1.resetTransform();
    cam1.setFov(60);
    cam1.clearParent();

    cam1.setPosition(ofGetWidth()/2, ofGetHeight()/2, 1000);
    cam1.lookAt(ofVec3f(ofGetWidth()/2, ofGetHeight()/2, -1));
}

void Renderer3D::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray);
    ofEnableDepthTest();

    ofEnableLighting();

    if(AppState::CAMERA == m_app->m_state){
        cam1.begin();
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
        }
    }

    if(AppState::CAMERA == m_app->m_state){
    ofPopMatrix();
    cam1.end();
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

void Renderer3D::imageExport(const string path, const string extension) const
{
    ofImage imageTemp;
    string fileName = path + "." + extension;



    imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    imageTemp.save(fileName);

    ofLog() << "<export image: " << fileName << ">";
}

void Renderer3D::drawCube3D(app::Cube3D *p_cube) {
    if (p_cube->isSelected()) {
        p_cube->setColorCube(m_app->renderer2d->colorSelected);
        ofSetColor(m_app->renderer2d->colorSelected);
    }
    else{
        p_cube->setColorCube(p_cube->getColorFill());
        ofSetColor(p_cube->getColorFill());
    }
    p_cube->draw();
}

void Renderer3D::drawSphere3D(app::Sphere3D *p_sphere) {
	ofShader shader;
	ofImage colormap, heightmap;
	ofxCubeMap myCubeMap = ofxCubeMap();
    if (p_sphere->isSelected()) {
        p_sphere->setColorSphere(m_app->renderer2d->colorSelected);
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
		shader.setUniform4f("col", ofFloatColor::red);
		shader.setUniform1i("maxHeight", 20);
		shader.setUniform1f("min", 0);
		p_sphere->draw();
		shader.end();
		ofEnableArbTex();

		break;
	case CUBE:
		shader.load("E:\\of_root\\apps\\myApps\\mySketch\\shaders\\CubeMap");
		myCubeMap.loadImages("e:\\of_root\\apps\\myApps\\mySketch\\data\\right.jpeg",
			"e:\\of_root\\apps\\myApps\\mySketch\\data\\left.jpeg",
			"e:\\of_root\\apps\\myApps\\mySketch\\data\\top.jpeg",
			"e:\\of_root\\apps\\myApps\\mySketch\\data\\base.jpeg",
			"e:\\of_root\\apps\\myApps\\mySketch\\data\\front.jpeg",
			"e:\\of_root\\apps\\myApps\\mySketch\\data\\back.jpeg");

		myCubeMap.bind();
		shader.begin();
		
		shader.setUniform1i("EnvMap", 0);
		shader.setUniform1f("reflectivity", 0.8);

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


