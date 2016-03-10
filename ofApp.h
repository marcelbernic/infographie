#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "CirclesRenderer.h"
#include "Coord.h"
#include "state.h"
#include "Obj2D.h"
#include <vector>

class ofApp : public ofBaseApp{
	private:
		std::vector<Coord> m_buffer;
		std::vector<Obj2D> m_obj2DVector;
		AppState m_state;
		int m_lineStroke;
		int m_lineColor;
		int m_lineColorSelected;
		int m_colorFill;
		int m_clickRadius;

	public:
		void setup();
		void update();
		void draw();

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

		void buildRectangle();
		void buildTriangle();
		void buildCircle();
		void buildLine();
		double calculateDistance(Coord p_coord1, Coord p_coord2);
		void clearSelected();
		void updateGroupSelection();

        ofxPanel gui, gui2;
		ofParameter<bool> vSync;
        ofParameter<bool> square;
        ofParameterGroup parameters, forms, menuBarParams;
		ofXml settings;
		CirclesRenderer renderer1,renderer2;
        ofTrueTypeFont font;
        ofxButton *buttonSquare;

		//Menu Bar
		ofxPanel menuBar;
		ofxButton *importButton, *exportButton;
};
