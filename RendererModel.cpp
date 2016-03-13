#include "RendererModel.h"

RendererModel::RendererModel() {

}


RendererModel::~RendererModel() {

}

void RendererModel::draw() {
	ofSetColor(255);
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	ofEnableDepthTest();
    #ifndef TARGET_PROGRAMMABLE_GL    
	glShadeModel(GL_SMOOTH); 
    #endif
	if(switchLight) light.enable();
	ofEnableSeparateSpecularLight();
	
	ofPushMatrix();
	ofTranslate(model.getPosition().x + 100, model.getPosition().y, 0);
	if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) ofRotate(ofGetMouseX(), 0, 1, 0);
	if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) ofRotate(ofGetMouseY(), 1, 0, 0);
	ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
	model.drawFaces();
	ofPopMatrix();

	ofDisableDepthTest();	
	light.disable();
	ofDisableLighting();
	ofDisableSeparateSpecularLight();

	ofSetColor(0, 0, 0);	
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate(), 2), 10, 150);
	ofDrawBitmapString("You are in Model Mode", 10, 165);
	ofDrawBitmapString("Files supported: '.obj', '.dae'", 10, 180);
	ofDrawBitmapString("To load a file click 'Import' ", 10, 195);

	ofDrawBitmapString("keys:", 10, 225);
	ofDrawBitmapString("Press l to turn on/off lightning", 10, 240);
	ofDrawBitmapString("Press m to turn on/off materials", 10, 255);
	ofDrawBitmapString("Press t to turn on/off textures", 10, 270);
	ofDrawBitmapString("Press left click to rotate", 10, 285);

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
			ofDisableArbTex(); // for models coords

			//Load model
			model.loadModel(p_file.getName());
			model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75, 0);
			mesh = model.getMesh(0);			
			
		}
	}
}