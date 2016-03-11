#include "Renderer2D.h"


Renderer2D::Renderer2D()
{
}


Renderer2D::~Renderer2D()
{
}

void Renderer2D::setup() {
	ofSetFrameRate(60);
	ofSetWindowShape(512, 512);

	//Default values:
	//strokeWidth
	//colorStroke
	//colorFill
}

void Renderer2D::draw() {
	ofBackgroundGradient(ofColor::white, ofColor::gray);

	//afficher zone selection

	// afficher le curseur
	/*ofSetLineWidth(2);
	ofSetColor(32);
	drawCursor(xMouseCurrent, yMouseCurrent);*/
}

// fonction qui dessine une zone rectangulaire
void Renderer2D::drawZone(float x1, float y1, float x2, float y2) const
{
	float x2Clamp = min(max(0.0f, x2), (float)ofGetWidth());
	float y2Clamp = min(max(0.0f, y2), (float)ofGetHeight());

	ofDrawRectangle(x1, y1, x2Clamp - x1, y2Clamp - y1);
}

//void Renderer::drawCursor(float x, float y) const
//{
//	float length = 10;
//	float offset = 5;
//
//	ofDrawLine(x + offset, y, x + offset + length, y);
//	ofDrawLine(x - offset, y, x - offset - length, y);
//	ofDrawLine(x, y + offset, x, y + offset + length);
//	ofDrawLine(x, y - offset, x, y - offset - length);
//}

void Renderer2D::imageExport(const string path, const string extension) const
{
	ofImage imageTemp;
	string fileName = path + "." + extension;



	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	imageTemp.save(fileName);

	ofLog() << "<export image: " << fileName << ">";
}