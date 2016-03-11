#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Renderer2D.h"
#include "Coord.h"
#include "state.h"
#include "Obj2D.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Line2D.h"
#include "Image2D.h"
#include "Obj2DCollection.h"
#include <vector>

class Renderer2D;

class ofApp : public ofBaseApp{
	public:

		std::vector<Coord> m_buffer;
		std::vector<Obj2D*> m_obj2DVector;
		AppState m_state;
		int m_lineStroke;
		int m_lineColor;
		int m_lineColorSelected;
		int m_colorFill;
		int m_clickRadius;
		bool isTakingScreenshot;

		ofApp();
		~ofApp();
		void exit();

		void setup();
		void update();
		void draw();
		void drawCursor();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void buttonPressed(const void * sender);
		
		void vSyncChanged(bool & vSync);
		void bLineChanged(bool & bLine);
		void bTriangleChanged(bool & bTriangle);
		void bRectangleChanged(bool & bRectangle);
		void bCircleChanged(bool & bCircle);
		void bSelectChanged(bool & bSelect);
		void clearButtons();

		void buildRectangle();
		void buildTriangle();
		void buildCircle();
		void buildLine();
		double calculateDistance(Coord p_coord1, Coord p_coord2);
		void clearSelected();
		void updateGroupSelection();
		void translateSelection(double p_x, double p_y);
		void rotateSelection();
		
		Renderer2D *renderer2d;
		void drawCollection(app::Obj2DCollection *p_coll);
		std::vector<Obj2D*> getCollectionObjects(app::Obj2DCollection* p_coll);

		ofxPanel shapesPanel, shapesParamsPanel, menuPanel;
		ofParameter<bool> vSync;
        ofParameter<bool> bLine, bTriangle, bRectangle, bCircle, bSelect;
        ofParameterGroup shapesSettingsParams, shapesParams, menuBarParams;
		ofXml settings;
        ofTrueTypeFont font;
		ofxButton *importButton, *exportButton, *mergeButton;
		//ofxButton *lineButton, *triangleButton, *rectangleButton, *circleButton;
};
