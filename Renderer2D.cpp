#include "Renderer2D.h"


Renderer2D::Renderer2D()
{
}


Renderer2D::~Renderer2D()
{
}

void Renderer2D::setup(const string p_name, ofApp *p_app) {
	ofSetFrameRate(60);

	m_app = p_app;

	//Default values:
	strokeWidth.set("Stroke Width", 5, 1, 10);
	colorStroke.set("Stroke Color", ofColor(0), ofColor(0,0), ofColor(255));
	colorFill.set("Fill Color", ofColor(255, 0, 0), ofColor(0, 0), ofColor(255));
	colorSelected.set("Selection Color", ofColor(255), ofColor(0, 0), ofColor(255));
	
	parameters.setName(p_name);
	parameters.add(strokeWidth);
	parameters.add(colorStroke);
	parameters.add(colorFill);
	parameters.add(colorSelected);

	strokeWidth.addListener(this, &Renderer2D::bStrokeWidthChanged);
	colorStroke.addListener(this, &Renderer2D::bColorStrokeChanged);
	colorFill.addListener(this, &Renderer2D::bColorFillChanged);
	colorSelected.addListener(this, &Renderer2D::bColorSelectedChanged);
}

void Renderer2D::draw() {
	ofBackgroundGradient(ofColor::white, ofColor::gray);

    ofSetColor(255);
    ofDisableLighting();

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
	for (Obj2D* o : m_app->m_obj2DVector) {
		switch (o->getType()) {
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
		}
	}
}

void Renderer2D::drawCircle(app::Circle *p_circle) {
	ofFill();	
	
	ofSetColor(p_circle->getColorFill());
	ofSetLineWidth(p_circle->getLineStroke());
	
	ofDrawCircle(p_circle->getCoordVector()[0].getX(), p_circle->getCoordVector()[0].getY(), p_circle->getRadius());
	ofNoFill();

	if (p_circle->isSelected()) {
		ofSetColor(p_circle->getLineColorSelected());
	}
	else {
		ofSetColor(p_circle->getLineColor());
	}
	ofDrawCircle(p_circle->getCoordVector()[0].getX(), p_circle->getCoordVector()[0].getY(), p_circle->getRadius());
	ofFill();
}

void Renderer2D::drawRectangle(app::Rectangle *p_rect) {
	ofFill();

	ofSetColor(p_rect->getColorFill());
	ofSetLineWidth(p_rect->getLineStroke());
	ofBeginShape();
	for (Coord c : p_rect->getCoordVector()) {
		ofVertex(c.getX(), c.getY());
	}
	ofEndShape();

	ofNoFill();
	if (p_rect->isSelected()) {
		ofSetColor(p_rect->getLineColorSelected());
	}
	else {
		ofSetColor(p_rect->getLineColor());
	}
	for (int i = 0; i < p_rect->getCoordVector().size() - 1; i++) {
		ofDrawLine(p_rect->getCoordVector()[i].getX(), p_rect->getCoordVector()[i].getY(), p_rect->getCoordVector()[i + 1].getX(), p_rect->getCoordVector()[i + 1].getY());
	}
	ofDrawLine(p_rect->getCoordVector()[3].getX(), p_rect->getCoordVector()[3].getY(), p_rect->getCoordVector()[0].getX(), p_rect->getCoordVector()[0].getY());
	ofFill();
	//ofDrawRectangle(p_rect->getCoordVector()[0].getX(), p_rect->getCoordVector()[0].getY(), p_rect->m_width, p_rect->m_height);
}

void Renderer2D::drawTriangle(app::Triangle *p_tri) {
	ofFill();
	ofSetColor(p_tri->getColorFill());
	ofSetLineWidth(p_tri->getLineStroke());
	ofDrawTriangle(p_tri->getCoordVector()[0].getX(), p_tri->getCoordVector()[0].getY(),
		p_tri->getCoordVector()[1].getX(), p_tri->getCoordVector()[1].getY(),
		p_tri->getCoordVector()[2].getX(), p_tri->getCoordVector()[2].getY());

	ofNoFill();
	if (p_tri->isSelected()) {
		ofSetColor(p_tri->getLineColorSelected());
	}
	else {
		ofSetColor(p_tri->getLineColor());
	}
	ofDrawTriangle(p_tri->getCoordVector()[0].getX(), p_tri->getCoordVector()[0].getY(),
		p_tri->getCoordVector()[1].getX(), p_tri->getCoordVector()[1].getY(),
		p_tri->getCoordVector()[2].getX(), p_tri->getCoordVector()[2].getY());
	ofFill();
}

void Renderer2D::drawLine(app::Line2D *p_line) {
	ofFill();
	ofSetLineWidth(p_line->getLineStroke());
	if (p_line->isSelected()) {
		ofSetColor(p_line->getLineColorSelected());		
	}
	else {
		ofSetColor(p_line->getLineColor());
	}
	ofDrawLine(p_line->getCoordVector()[0].getX(), p_line->getCoordVector()[0].getY(),
		p_line->getCoordVector()[1].getX(), p_line->getCoordVector()[1].getY());
}

void Renderer2D::drawImage(app::Image2D *p_image) {
	ofSetColor(255);
	ofNoFill();
	if (p_image->isSelected()) {
		ofFill();
		ofSetColor(255, 0, 0);
		ofSetLineWidth(p_image->getLineStroke());
	}
	ofImage img = p_image->getImage();
	ofTranslate(p_image->getCoordVector()[0].getX(), p_image->getCoordVector()[0].getY());
	ofRotate(p_image->getAngle());
	img.getTextureReference().draw(0, 0, p_image->getWidth(), p_image->getHeight());
	ofRotate(-p_image->getAngle());
	ofTranslate(-p_image->getCoordVector()[0].getX(), -p_image->getCoordVector()[0].getY());
	ofFill();

	//img.getTextureReference().unbind()
}

void Renderer2D::drawCollection(app::Obj2DCollection *p_coll) {
	for (Obj2D* o : p_coll->getObjVector()) {
		switch (o->getType()) {
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
		}
	}
}

void Renderer2D::bStrokeWidthChanged(int & p_strokeWidth) {
	for (Obj2D* o : m_app->m_obj2DVector) {
		if (o->isSelected()) {
			o->setLineStroke(p_strokeWidth);
		}
	}
}
void Renderer2D::bColorStrokeChanged(ofColor & p_colorStroke) {
	for (Obj2D* o : m_app->m_obj2DVector) {
		if (o->isSelected()) {
			o->setLineColor(p_colorStroke);
		}
	}
}
void Renderer2D::bColorFillChanged(ofColor & p_colorFill) {
	for (Obj2D* o : m_app->m_obj2DVector) {
		if (o->isSelected()) {
			o->setColorFill(p_colorFill);
		}
	}
    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            o->setColorFill(p_colorFill);
        }
    }
}
void Renderer2D::bColorSelectedChanged(ofColor & p_colorSelected) {
	for (Obj2D* o : m_app->m_obj2DVector) {
		if (o->isSelected()) {
			o->setLineColorSelected(p_colorSelected);
		}
    }

    for (Obj3D* o : m_app->m_obj3DVector) {
        if (o->isSelected()) {
            o->setLineColorSelected(p_colorSelected);
        }
    }
}

void Renderer2D::imageExport(const string path, const string extension) const
{
	ofImage imageTemp;
	string fileName = path + "." + extension;



	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}
