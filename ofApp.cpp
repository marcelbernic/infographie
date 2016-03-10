#include "ofApp.h"
#include <ostream>

//--------------------------------------------------------------
void ofApp::setup(){
	renderer1.setup("renderer1");
	renderer2.setup("renderer2");

	//Parameters
	m_state = AppState::ACTION_SELECT;
	m_lineStroke = 5;
	m_clickRadius = 5;
    forms.setName("Formes");
    forms.add(square.set("square", true));
	parameters.setName("settings");
	parameters.add(vSync.set("vSync",true));
	parameters.add(renderer1.parameters);
	parameters.add(renderer2.parameters);
	menuBarParams.setName("Menu");
	importButton = new ofxButton();
	exportButton = new ofxButton();
	importButton->setup("Import");
	exportButton->setup("Export");

	//Setup panels
	menuBar.setup(menuBarParams);
	menuBar.add(importButton);
	menuBar.add(exportButton);
	gui.setup(parameters);
    gui2.setup(forms);


    buttonSquare = new ofxButton();
    buttonSquare->setup("Square", 19);

	menuBar.setPosition(10, 0);
    gui2.setPosition(10, 15 + menuBar.getHeight());
    gui.setPosition(10, 10 + gui2.getHeight() + menuBar.getHeight() + 15);
	buttonSquare->setPosition(10, 20 + gui.getHeight() + gui2.getHeight() + menuBar.getHeight());

    buttonSquare->addListener(this, &ofApp::buttonPressed);
	importButton->addListener(this, &ofApp::buttonPressed);
	exportButton->addListener(this, &ofApp::buttonPressed);

    gui.loadFromFile("settings.xml");

    font.load( OF_TTF_SANS,9,true,true);
    ofEnableAlphaBlending();

}

void ofApp::vSyncChanged(bool & vSync){
	ofSetVerticalSync(vSync);
}


//--------------------------------------------------------------
void ofApp::update(){
	// frameNum is a readonly parameter so this will fail to compile
	// unless we are inside the CirclesRenderer class
	// renderer.frameNum = 5;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor::white, ofColor::gray);
	renderer1.draw();
	renderer2.draw();
	ofSetColor(255);
	menuBar.draw();
    gui.draw();
    gui2.draw();
	font.drawString("frame: " + ofToString(renderer1.frameNum),ofGetWidth()-150,20);
	font.drawString("fps: " + ofToString((int)ofGetFrameRate()),ofGetWidth()-150,40);
    buttonSquare->draw();

	switch (m_state) {
	case AppState::ACTION_GROUPSELECT:
		ofSetColor(255, 0, 0);
		ofSetLineWidth(5);
		ofNoFill();
		ofDrawRectangle(m_buffer[0].getX(), m_buffer[0].getY(), m_buffer[1].getX() - m_buffer[0].getX(), m_buffer[1].getY() - m_buffer[0].getY());
		ofFill();
		break;
	case AppState::BUILD_CIRCLE:
		if (m_buffer.size() == 1) {
			ofSetColor(255, 0, 0);
			ofSetLineWidth(m_lineStroke);
			ofDrawCircle(m_buffer[0].getX(), m_buffer[0].getY(), calculateDistance(m_buffer[0], Coord(ofGetMouseX(), ofGetMouseY())));
		}		
		break;
	case AppState::BUILD_RECTANGLE:
		if (m_buffer.size() == 1) {
			ofSetColor(255, 0, 0);
			ofSetLineWidth(m_lineStroke);
			ofDrawRectangle(m_buffer[0].getX(), m_buffer[0].getY(), ofGetMouseX() - m_buffer[0].getX(), ofGetMouseY() - m_buffer[0].getY());
		}
		break;
	case AppState::BUILD_TRIANGLE:
		ofSetColor(255, 0, 0);
		ofSetLineWidth(m_lineStroke);
		if (m_buffer.size() == 1) {
			ofDrawLine(m_buffer[0].getX(), m_buffer[0].getY(), ofGetMouseX(), ofGetMouseY());
		}
		if (m_buffer.size() == 2) {
			ofDrawTriangle(m_buffer[0].getX(), m_buffer[0].getY(), m_buffer[1].getX(), m_buffer[1].getY(), ofGetMouseX(), ofGetMouseY());
		}
		break;
	case AppState::BUILD_LINE:		
		if (m_buffer.size() == 1) {
			ofSetColor(255, 0, 0);
			ofSetLineWidth(m_lineStroke);
			ofDrawLine(m_buffer[0].getX(), m_buffer[0].getY(), ofGetMouseX(), ofGetMouseY());
		}
		break;
	}
	for (Obj2D* o : m_obj2DVector) {
		switch (o->getType()) {
			case EnumVectorDrawMode::VECTOR_PRIMITIVE_CIRCLE: {
				app::Circle* c = dynamic_cast<app::Circle*>(o);
				//drawcircle(c);
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
		}

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	/*if(key=='s'){
		settings.serialize(parameters);
		settings.save("settings.xml");
	}
	if(key=='l'){
		settings.load("settings.xml");
		settings.deserialize(parameters);
	}
	if(key=='o'){
		cout << renderer1.parameters;
		cout << renderer2.parameters;
	}
	if(key=='r'){
		renderer1.color = ofColor(127);
		renderer2.color = ofColor(127);
	}*/
	if (key == 's') {
		m_state = AppState::ACTION_SELECT;
		m_buffer.clear();
	}
	if (key == 'l') {
		m_state = AppState::BUILD_LINE;
		m_buffer.clear();
	}
	if (key == 'c') {
		m_state = AppState::BUILD_CIRCLE;
		m_buffer.clear();
	}
	if (key == 'r') {
		m_state = AppState::BUILD_RECTANGLE;
		m_buffer.clear();
	}
	if (key == 't') {
		m_state = AppState::BUILD_TRIANGLE;
		m_buffer.clear();
	}
}

void ofApp::buttonPressed(const void * sender){
    ofxButton * button = (ofxButton*)sender;
	string btnName = button->getName();

	if (btnName == "Import") {

	}
    ofLog() << "Test button pressed";
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	switch (m_state) {
		case AppState::ACTION_SELECT:
			m_buffer.push_back(Coord(x, y));
			m_state = AppState::ACTION_GROUPSELECT;
			break;
		case AppState::ACTION_GROUPSELECT:
			m_buffer[1].setX(x);
			m_buffer[1].setY(y);
			updateGroupSelection();
			break;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	switch (m_state) {
		case AppState::BUILD_RECTANGLE:
			m_buffer.push_back(Coord(x, y));
			if (m_buffer.size() == 2) {
				buildRectangle();
				m_buffer.clear();
			}
			break;
		case AppState::BUILD_TRIANGLE:
			m_buffer.push_back(Coord(x, y));
			if (m_buffer.size() == 3) {
				buildTriangle();
				m_buffer.clear();
			}
			break;
		case AppState::BUILD_CIRCLE:
			m_buffer.push_back(Coord(x, y));
			if (m_buffer.size() == 2) {
				buildCircle();
				m_buffer.clear();
			}
			break;
		case AppState::BUILD_LINE:
			m_buffer.push_back(Coord(x, y));
			if (m_buffer.size() == 2) {
				buildLine();
				m_buffer.clear();
			}
			break;
		case AppState::ACTION_SELECT:
			m_buffer.clear();
			m_buffer.push_back(Coord(x, y));
			if (!(ofGetKeyPressed(OF_KEY_LEFT_CONTROL) || ofGetKeyPressed(OF_KEY_RIGHT_CONTROL))) {
				clearSelected();
			}
			for (Obj2D* o : m_obj2DVector) {
				if (o->checkSelected(Coord(x, y), m_clickRadius)) {
					break;
				}				
			}
			break;
	}		
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	switch (m_state) {
	case AppState::ACTION_GROUPSELECT:
		m_buffer.clear();
		m_state = AppState::ACTION_SELECT;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::buildRectangle() {
	double width = m_buffer[1].getX() - m_buffer[0].getX();
	double height = m_buffer[1].getY() - m_buffer[0].getY();
	if (width >= 0 && height >= 0) { //0 = top-left, 1 = bottom-right
		m_obj2DVector.push_back(new app::Rectangle(m_buffer[0], width, height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
	else if (width < 0 && height >= 0) { //0 = top-right, 1 = bottom-left
		m_obj2DVector.push_back(new app::Rectangle(Coord(m_buffer[1].getX(), m_buffer[0].getY()), -width, height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
	else if (width >= 0 && height < 0) { //0 = bottom-left, 1 = top-right
		m_obj2DVector.push_back(new app::Rectangle(Coord(m_buffer[0].getX(), m_buffer[1].getY()), width, -height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
	else { //0 = bottom-right, 1 = top-left
		m_obj2DVector.push_back(new app::Rectangle(m_buffer[1], -width, -height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
}

void ofApp::buildTriangle() {
	m_obj2DVector.push_back(new app::Triangle(m_buffer, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
}

void ofApp::buildCircle() {
	double radius = calculateDistance(m_buffer[0], m_buffer[1]);
	m_obj2DVector.push_back(new app::Circle(m_buffer[0], radius, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
}

void ofApp::buildLine() {
	m_obj2DVector.push_back(new app::Line2D(m_buffer, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
}

double ofApp::calculateDistance(Coord p_coord1, Coord p_coord2) {
	double x2 = pow((p_coord1.getX() - p_coord2.getX()), 2);
	double y2 = pow((p_coord1.getY() - p_coord2.getY()), 2);
	return sqrt(x2 + y2);
}

void ofApp::clearSelected() {
	for (Obj2D* o : m_obj2DVector) {
		o->setSelected(false);
	}
}

void ofApp::updateGroupSelection() {
	double width = m_buffer[1].getX() - m_buffer[0].getX();
	double height = m_buffer[1].getY() - m_buffer[0].getY();
	Coord topLeft = Coord(0,0);
	if (width >= 0 && height >= 0) { //0 = top-left, 1 = bottom-right
		topLeft = m_buffer[0];
		//cout << "TOP-LEFT" << endl;
	}
	else if (width < 0 && height >= 0) { //0 = top-right, 1 = bottom-left
		topLeft = Coord(m_buffer[1].getX(), m_buffer[0].getY());
		//cout << "TOP-RIGHT" << endl;
	}
	else if (width >= 0 && height < 0) { //0 = bottom-left, 1 = top-right
		topLeft = Coord(m_buffer[0].getX(), m_buffer[1].getY());
		//cout << "BOTTOM-LEFT" << endl;
	}
	else { //0 = bottom-right, 1 = top-left
		topLeft = m_buffer[1];
		//cout << "BOTTOM-RIGHT" << endl;
	}
	for (Obj2D* o : m_obj2DVector) {
		cout << topLeft.getX() << " " << topLeft.getY() << abs(width) << " " << abs(height) << endl;
		o->setSelected(o->containedInRect(topLeft, abs(width), abs(height)));
	}
}

//void ofApp::drawCircle(app::Circle *p_circle) {
//	if (p_circle->isSelected()) {
//		ofSetColor(255, 255, 255);
//		ofSetLineWidth(p_circle->getLineStroke());
//	}
//	else {
//		ofSetColor(255, 0, 0);
//		ofSetLineWidth(p_circle->getLineStroke());
//	}
//	ofDrawCircle(p_circle->getCoordVector()[0].getX(), p_circle->getCoordVector()[0].getY(), p_circle->getRadius());
//}

void ofApp::drawRectangle(app::Rectangle *p_rect) {
	if (p_rect->isSelected()) {
		ofSetColor(255, 255, 255);
		ofSetLineWidth(p_rect->getLineStroke());
	}
	else {
		ofSetColor(255, 0, 0);
		ofSetLineWidth(p_rect->getLineStroke());
	}
	ofDrawRectangle(p_rect->getCoordVector()[0].getX(), p_rect->getCoordVector()[0].getY(), p_rect->m_width, p_rect->m_height);
}

void ofApp::drawTriangle(app::Triangle *p_tri) {
	if (p_tri->isSelected()) {
		ofSetColor(255, 255, 255);
		ofSetLineWidth(p_tri->getLineStroke());
	}
	else {
		ofSetColor(255, 0, 0);
		ofSetLineWidth(p_tri->getLineStroke());
	}
	ofDrawTriangle(p_tri->getCoordVector()[0].getX(), p_tri->getCoordVector()[0].getY(), 
		p_tri->getCoordVector()[1].getX(), p_tri->getCoordVector()[1].getY(), 
		p_tri->getCoordVector()[2].getX(), p_tri->getCoordVector()[2].getY());
}

void ofApp::drawLine(app::Line2D *p_line) {
	if (p_line->isSelected()) {
		ofSetColor(255, 255, 255);
		ofSetLineWidth(p_line->getLineStroke());
	}
	else {
		ofSetColor(255, 0, 0);
		ofSetLineWidth(p_line->getLineStroke());
	}
	ofDrawLine(p_line->getCoordVector()[0].getX(), p_line->getCoordVector()[0].getY(), 
		p_line->getCoordVector()[1].getX(), p_line->getCoordVector()[1].getY());
}

void ofApp::drawImage(app::Image2D *p_image) {

}
