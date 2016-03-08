#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	renderer1.setup("renderer1");
	renderer2.setup("renderer2");

	//Parameters
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

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
