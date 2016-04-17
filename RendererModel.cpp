#include "RendererModel.h"

RendererModel::RendererModel() {

}

RendererModel::~RendererModel() {

}


void RendererModel::setup() {
	ofSetBoxResolution(30, 30, 30);

	cam.disableMouseInput();
	cam.setDistance(10);
	cam.setPosition(0, 0, -50);
	cam.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	cam.setNearClip(1);
	cam.setFarClip(150);

	cam.enableMouseInput();

	// range of the shadow camera //
	shadow.setRange(10, 150);
	shadow.setBias(0.01);

}

void RendererModel::update() {

	shadow.setLightPosition(ofVec3f(cos(ofGetElapsedTimef()*0.6) * 10, -3, -25));
	shadow.setLightLookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));

	// Control model position
	if (ofGetKeyPressed(OF_KEY_LEFT) && ofGetKeyPressed(OF_KEY_CONTROL)) {
		model.setRotation(1, model.getPosition().x - 2, 0, 1, 0);
	}
	if (ofGetKeyPressed(OF_KEY_RIGHT) && ofGetKeyPressed(OF_KEY_CONTROL)) {
		model.setRotation(1, model.getPosition().x + 2, 0, 1, 0);
	}
	if (ofGetKeyPressed(OF_KEY_DOWN) && ofGetKeyPressed(OF_KEY_CONTROL)) {
		model.setRotation(1, model.getPosition().y - 2, 1, 0, 0);
	}
	if (ofGetKeyPressed(OF_KEY_UP) && ofGetKeyPressed(OF_KEY_CONTROL)) {
		model.setRotation(1, model.getPosition().y + 2, 1, 0, 0);
	}
	if (ofGetKeyPressed(OF_KEY_RIGHT)) {
		model.setPosition(model.getPosition().x + 5, model.getPosition().y, model.getPosition().z);
	}
	if (ofGetKeyPressed(OF_KEY_LEFT)) {
		model.setPosition(model.getPosition().x - 5, model.getPosition().y, model.getPosition().z);
	}
	if (ofGetKeyPressed(OF_KEY_UP)) {
		model.setPosition(model.getPosition().x, model.getPosition().y + 5, model.getPosition().z);
	}
	if (ofGetKeyPressed(OF_KEY_DOWN)) {
		model.setPosition(model.getPosition().x, model.getPosition().y - 5, model.getPosition().z);
	}
	if (ofGetKeyPressed(OF_KEY_UP) && ofGetKeyPressed(OF_KEY_LEFT_ALT)) {
		model.setPosition(model.getPosition().x, model.getPosition().y, model.getPosition().z + 5);
	}
	if (ofGetKeyPressed(OF_KEY_DOWN) && ofGetKeyPressed(OF_KEY_LEFT_ALT)) {
		model.setPosition(model.getPosition().x, model.getPosition().y, model.getPosition().z - 5);
	}
	// end control model position
}

void RendererModel::draw() {
	
	shadow.beginDepthPass();
	glEnable(GL_DEPTH_TEST);
	rendererScene();
	glDisable(GL_DEPTH_TEST);
	shadow.endDepthPass();


	shadow.beginRenderPass(cam);
	cam.begin();
	glEnable(GL_DEPTH_TEST);
	rendererScene();
	glDisable(GL_DEPTH_TEST);
	cam.end();
	shadow.endRenderPass();
	RendererModel::update();

}

void RendererModel::rendererScene() {
	ofSetColor(255);
	ofPushMatrix(); {
		ofTranslate(0, 0, 0);
		ofRotate(180, 1, 0, 0);
		ofScale(0.015, 0.015, 0.015);
		model.drawFaces();
	} ofPopMatrix();

	/*ofSetColor(241, 238, 162);
	ofPushMatrix(); {
		ofRotateX(cos(ofGetElapsedTimef() * 2.3) * sin(ofGetElapsedTimef()) * RAD_TO_DEG);
		ofRotateY(sin(ofGetElapsedTimef()) * RAD_TO_DEG);
		ofDrawBox(2, 2, 2);
	} ofPopMatrix();*/

	ofSetColor(128, 158, 108);
	ofDrawSphere(-8, sin(ofGetElapsedTimef()) * 5, 2);

	/*
	ofSetColor(183, 241, 195);
	ofDrawSphere(24, sin(ofGetElapsedTimef() * 0.3) * 3, 5, 2);*/

	// draw 2 boxes to visualize l'effect of shadows
	ofSetColor(95, 144, 151);
	ofDrawBox(0, 5, 0, 250, 2, 250);

	ofDrawBox(0, -8, 10, 140, 50, 2);
}


void RendererModel::processOpenFileSelection(ofFileDialogResult p_file) {
	ofLogVerbose("getName(): " + p_file.getName());
	ofLogVerbose("getPath(): " + p_file.getPath());

	ofFile file(p_file.getPath());

	if (file.exists()) {
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());

		//We only want .obj, .dae files
		if (fileExtension == "OBJ" || fileExtension == "DAE") {

			// initial parameters
			switchTextures = true;
			switchLight = true;
			switchMaterials = false;
			//ofDisableArbTex(); // for models coords

			//Load model and initialize
			model.loadModel(p_file.getName());
			model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.5, 0);
			mesh = model.getMesh(0);

			
		}
	}
}

