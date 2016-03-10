#include "ofApp.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Line2D.h"
#include "Image2D.h"

//--------------------------------------------------------------
void ofApp::setup(){
	renderer1.setup("renderer1");
	renderer2.setup("renderer2");

	//Parameters
	m_state = AppState::ACTION_SELECT;
	m_lineStroke = 5;
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key=='s'){
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
			if (ofGetKeyPressed(OF_KEY_LEFT_CONTROL) || ofGetKeyPressed(OF_KEY_RIGHT_CONTROL)) {
				clearSelected();
			}
			for (Obj2D o : m_obj2DVector) {
				o.checkSelected(Coord(x, y), m_clickRadius);
				break;
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
		m_obj2DVector.push_back(app::Rectangle(m_buffer[0], width, height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
	if (width < 0 && height >= 0) { //0 = top-right, 1 = bottom-left
		m_obj2DVector.push_back(app::Rectangle(Coord(m_buffer[1].getX(), m_buffer[0].getY()), -width, height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
	if (width >= 0 && height < 0) { //0 = bottom-left, 1 = top-right
		m_obj2DVector.push_back(app::Rectangle(Coord(m_buffer[0].getX(), m_buffer[1].getY()), width, -height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
	else { //0 = bottom-right, 1 = top-left
		m_obj2DVector.push_back(app::Rectangle(m_buffer[1], -width, -height, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
	}
}

void ofApp::buildTriangle() {
	m_obj2DVector.push_back(app::Triangle(m_buffer, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
}

void ofApp::buildCircle() {
	double radius = calculateDistance(m_buffer[0], m_buffer[1]);
	m_obj2DVector.push_back(app::Circle(m_buffer[0], radius, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
}

void ofApp::buildLine() {
	m_obj2DVector.push_back(app::Line2D(m_buffer, 0, m_lineStroke, m_lineColor, m_lineColorSelected, m_colorFill));
}

double ofApp::calculateDistance(Coord p_coord1, Coord p_coord2) {
	double x2 = pow((p_coord1.getX() - p_coord2.getX()), 2);
	double y2 = pow((p_coord1.getY() - p_coord2.getY()), 2);
	return sqrt(x2 + y2);
}

void ofApp::clearSelected() {
	for (Obj2D o : m_obj2DVector) {
		o.setSelected(false);
	}
}

void ofApp::updateGroupSelection() {
	double width = m_buffer[1].getX() - m_buffer[0].getX();
	double height = m_buffer[1].getY() - m_buffer[0].getY();
	Coord topLeft = Coord(0,0);
	if (width >= 0 && height >= 0) { //0 = top-left, 1 = bottom-right
		Coord topLeft = m_buffer[0];
	}
	if (width < 0 && height >= 0) { //0 = top-right, 1 = bottom-left
		Coord topLeft = Coord(m_buffer[1].getX(), m_buffer[0].getY());
	}
	if (width >= 0 && height < 0) { //0 = bottom-left, 1 = top-right
		Coord topLeft = Coord(m_buffer[0].getX(), m_buffer[1].getY());
	}
	else { //0 = bottom-right, 1 = top-left
		Coord topLeft = m_buffer[1];
	}
	for (Obj2D o : m_obj2DVector) {
		o.setSelected(o.containedInRect(topLeft, abs(width), abs(height)));
	}
}
