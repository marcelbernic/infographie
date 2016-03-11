#pragma once

//#include "ofMain.h"
#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "ofApp.h"
#include "Obj2D.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Line2D.h"
#include "Image2D.h"
#include "Obj2DCollection.h"

class Renderer2D;
class ofApp;

template<typename ParameterType>
class ofRendererParam : public ofReadOnlyParameter<ParameterType, Renderer2D> {
	friend class Renderer2D;
};

class Renderer2D
{
private:
	ofApp * m_app;
public:
	Renderer2D();
	~Renderer2D();

	void setup(const string p_name, ofApp *p_app);
	
	void draw();
	void drawCircle(app::Circle *p_circle);
	void drawRectangle(app::Rectangle *p_rect);
	void drawTriangle(app::Triangle *p_triangle);
	void drawLine(app::Line2D *p_line);
	void drawImage(app::Image2D *p_image);
	void drawCollection(app::Obj2DCollection *p_coll);

	void imageExport(const string path, const string extension) const;

	void bStrokeWidthChanged(int & p_strokeWidth);
	void bColorStrokeChanged(ofColor & p_colorStroke);
	void bColorFillChanged(ofColor & p_colorFill);
	void bColorSelectedChanged(ofColor & p_colorSelected);

	ofParameterGroup parameters;
	//ofParameter<float> size;
	ofParameter<int> strokeWidth;
	//ofParameter<ofVec2f> position;
	ofParameter<ofColor> colorStroke;
	ofParameter<ofColor> colorFill;
	ofParameter<ofColor> colorSelected;
};

