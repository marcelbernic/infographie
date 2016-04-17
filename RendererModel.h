#pragma once

#include "ofApp.h"
#include "ofxAssimpModelLoader.h" 
#include "ofVboMesh.h"
#include "ofxShadowSimple.h"

class RendererModel;
class ofApp;

class RendererModel
{
private:
	ofApp * m_app;
public:
	RendererModel();
	~RendererModel();

	void setup();
	void draw();
	void update();

	void rendererScene();

	void processOpenFileSelection(ofFileDialogResult p_file);

	ofxAssimpModelLoader model;
	ofMesh mesh;
	//ofLight	light;

	bool switchLight;
	bool switchMaterials;
	bool switchTextures;
	
	ofEasyCam cam;
	ofxShadowSimple shadow;
};

