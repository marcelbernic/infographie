#include "Renderer3D.h"

Renderer3D::Renderer3D()
{
}


Renderer3D::~Renderer3D()
{
}

void Renderer3D::setup(const string p_name, ofApp *p_app) {
    ofSetFrameRate(60);
    ofSetWindowShape(1024, 768);

    m_app = p_app;

    //Default values:
    x.set("Position x", 0, 0, 1024);
    y.set("Position y", 0, 0, 768);
    z.set("Position z", 0, -300, 300);

    rotx.set("Rotate axe x", 0, 0.0, 360);
    roty.set("Rotate axe y", 0, 0.0, 360);
    rotz.set("Rotate axe z", 0, 0.0, 360);

    parameters3D.setName(p_name);
    parameters3D.add(x);
    parameters3D.add(y);
    parameters3D.add(z);

    parameters3D.add(rotx);
    parameters3D.add(roty);
    parameters3D.add(rotz);

    x.addListener(this, &Renderer3D::xChanged);
    y.addListener(this, &Renderer3D::yChanged);
    z.addListener(this, &Renderer3D::zChanged);

    rotx.addListener(this, &Renderer3D::rotxChanged);
    roty.addListener(this, &Renderer3D::rotyChanged);
    rotz.addListener(this, &Renderer3D::rotzChanged);
}

void Renderer3D::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray);

    ofSetColor(255);
    if (!m_app->isTakingScreenshot) {
        switch (m_app->m_state) {
        case AppState::BUILD_CUBE:
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
        }
    }
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
    }
    else{
        p_cube->setColorCube(p_cube->getColorFill());
    }
    p_cube->draw();
}
