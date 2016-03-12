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
    strokeWidth.set("Stroke Width", 5, 0, 10);
    colorStroke.set("Stroke Color", ofColor(0), ofColor(0,0), ofColor(255));
    colorFill.set("Fill Color", ofColor(255, 0, 0), ofColor(0, 0), ofColor(255));
    colorSelected.set("Selection Color", ofColor(255), ofColor(0, 0), ofColor(255));

    parameters.setName(p_name);
    parameters.add(strokeWidth);
    parameters.add(colorStroke);
    parameters.add(colorFill);
    parameters.add(colorSelected);

    strokeWidth.addListener(this, &Renderer3D::bStrokeWidthChanged);
    colorStroke.addListener(this, &Renderer3D::bColorStrokeChanged);
    colorFill.addListener(this, &Renderer3D::bColorFillChanged);
    colorSelected.addListener(this, &Renderer3D::bColorSelectedChanged);
}

void Renderer3D::draw() {
    ofBackgroundGradient(ofColor::white, ofColor::gray);

    ofSetColor(255);

    if (!m_app->isTakingScreenshot) {
        switch (m_app->m_state) {
        case AppState::ACTION_GROUPSELECT:
            ofSetColor(255, 0, 0);
            ofSetLineWidth(5);
            ofNoFill();
            ofDrawRectangle(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), m_app->m_buffer[1].getX() - m_app->m_buffer[0].getX(), m_app->m_buffer[1].getY() - m_app->m_buffer[0].getY());
            ofFill();
            break;
        case AppState::BUILD_CIRCLE:
            if (m_app->m_buffer.size() == 1) {
                ofSetColor(colorFill);
                ofSetLineWidth(strokeWidth);
                ofDrawCircle(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), m_app->calculateDistance(m_app->m_buffer[0], Coord(ofGetMouseX(), ofGetMouseY())));
                ofNoFill();
                ofSetColor(colorStroke);
                ofDrawCircle(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), m_app->calculateDistance(m_app->m_buffer[0], Coord(ofGetMouseX(), ofGetMouseY())));
                ofFill();
            }
            break;
        case AppState::BUILD_RECTANGLE:
            if (m_app->m_buffer.size() == 1) {
                ofSetColor(colorFill);
                ofSetLineWidth(strokeWidth);
                ofDrawRectangle(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), ofGetMouseX() - m_app->m_buffer[0].getX(), ofGetMouseY() - m_app->m_buffer[0].getY());
                ofNoFill();
                ofSetColor(colorStroke);
                ofDrawRectangle(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), ofGetMouseX() - m_app->m_buffer[0].getX(), ofGetMouseY() - m_app->m_buffer[0].getY());
                ofFill();
            }
            break;
        case AppState::BUILD_TRIANGLE:
            ofSetLineWidth(strokeWidth);
            if (m_app->m_buffer.size() == 1) {
                ofSetColor(colorStroke);
                ofDrawLine(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), ofGetMouseX(), ofGetMouseY());
            }
            if (m_app->m_buffer.size() == 2) {
                ofSetColor(colorFill);
                ofDrawTriangle(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), m_app->m_buffer[1].getX(), m_app->m_buffer[1].getY(), ofGetMouseX(), ofGetMouseY());
                ofNoFill();
                ofSetColor(colorStroke);
                ofDrawTriangle(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), m_app->m_buffer[1].getX(), m_app->m_buffer[1].getY(), ofGetMouseX(), ofGetMouseY());
                ofFill();
            }
            break;
        case AppState::BUILD_LINE:
            if (m_app->m_buffer.size() == 1) {
                ofSetColor(colorStroke);
                ofSetLineWidth(strokeWidth);
                ofDrawLine(m_app->m_buffer[0].getX(), m_app->m_buffer[0].getY(), ofGetMouseX(), ofGetMouseY());
            }
            break;
        }
    }
    for (Obj3D* o : m_app->m_obj3DVector) {
        /*switch (o->getType()) {
        case EnumVectorDrawMode::VECTOR_PRIMITIVE_CIRCLE: {
            app::Circle* c = dynamic_cast<app::Circle*>(o);
            drawCircle(c);
        }
            break;
        case EnumVectorDrawMode::VECTOR_PRIMITIVE_RECTANGLE: {
            app::Rectangle* r = dynamic_cast<app::Rectangle*>(o);
            drawRectangle(r);
        }
            break;
        case EnumVectorDrawMode::VECTOR_PRIMITIVE_TRIANGLE: {
            app::Triangle* t = dynamic_cast<app::Triangle*>(o);
            drawTriangle(t);
        }
            break;
        case EnumVectorDrawMode::VECTOR_PRIMITIVE_LINE: {
            app::Line2D* l = dynamic_cast<app::Line2D*>(o);
            drawLine(l);
        }
            break;
        case EnumVectorDrawMode::VECTOR_PRIMITIVE_IMAGE: {
            app::Image2D* i = dynamic_cast<app::Image2D*>(o);
            drawImage(i);
        }
            break;
        case EnumVectorDrawMode::VECTOR_PRIMITIVE_COLLECTION: {
            app::Obj2DCollection* i = dynamic_cast<app::Obj2DCollection*>(o);
            drawCollection(i);
        }
            break;
        }*/
    }
}



void Renderer3D::bStrokeWidthChanged(int & p_strokeWidth) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            o->setLineStroke(p_strokeWidth);
        }
    }
}
void Renderer3D::bColorStrokeChanged(ofColor & p_colorStroke) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            o->setLineColor(p_colorStroke);
        }
    }
}
void Renderer3D::bColorFillChanged(ofColor & p_colorFill) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            o->setColorFill(p_colorFill);
        }
    }
}
void Renderer3D::bColorSelectedChanged(ofColor & p_colorSelected) {
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            o->setLineColorSelected(p_colorSelected);
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
