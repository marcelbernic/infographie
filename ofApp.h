#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "of3dGraphics.h"
#include "of3dPrimitives.h"
#include "of3dUtils.h"
#include "Renderer2D.h"
#include "Renderer3D.h"
#include "Coord.h"
#include "state.h"
#include "Obj2D.h"
#include "Obj3D.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "Line2D.h"
#include "Image2D.h"
#include "Cube3D.h"
#include "Obj2DCollection.h"
#include <vector>
#include "RendererModel.h"
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h" 

class Renderer2D;
class Obj3D;
class Renderer3D;
class RendererModel;

class ofApp : public ofBaseApp{
	public:

		std::vector<Coord> m_buffer;
		std::vector<Obj2D*> m_obj2DVector;
        std::vector<Coord3D> m_buffer3D;
        std::vector<Obj3D*> m_obj3DVector;
		AppState m_state;
		AppMode m_mode;
		int m_clickRadius;
		bool isTakingScreenshot;
		bool isClearingButtonsShapes, isClearingButtonsModes;
        bool m_firstTimeSelection;
        int m_selectionIndex;

		ofApp();
		~ofApp();
		void exit();

		void setup();
		void update();
		void draw();
		void drawCursor();
		bool mouseIsOverPanel();

		void keyPressed(int key);
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
		void b2DChanged(bool & p_2D);
		void b3DChanged(bool & p_3D);
		void bModelModeChanged(bool & p_modelMode); //*
		void bLineChanged(bool & p_Line);
		void bTriangleChanged(bool & p_Triangle);
		void bRectangleChanged(bool & p_Rectangle);
		void bCircleChanged(bool & p_Circle);
		void bSelectChanged(bool & p_Select);
        void bCubeChanged(bool & p_cube);
        void bSphereChanged(bool & p_sphere);
        void bCameraChanged(bool & p_sphere);
        void bCloud(bool & p_Cloud);
		void clearButtons();

		void buildRectangle();
		void buildTriangle();
		void buildCircle();
		void buildLine();
        void buildCube();
        void buildSphere();
		double calculateDistance(Coord p_coord1, Coord p_coord2);
		void clearSelected();
		void updateGroupSelection();
		void translateSelection(double p_x, double p_y);
		void resizeSelection();
		void rotateSelection();
		void deleteSelection();
        void deleteSelection3D();
        void clear2DButtons();
        void clear3DButtons();
		
		Renderer2D *renderer2d;
        Renderer3D *renderer3d;

		std::vector<Obj2D*> getCollectionObjects(app::Obj2DCollection* p_coll);

        ofxPanel shapesPanel, shapesParamsPanel, menuPanel, shapes3DPanel, shapes3DParamsPanel;
		ofParameter<bool> vSync;
		ofParameter<bool> b2D, b3D, bModelMode; //*
        ofParameter<bool> bLine, bTriangle, bRectangle, bCircle, bSelect;
        ofParameter<bool> bCube, bSphere, bCamera;
        ofParameterGroup shapesSettingsParams, shapesParams, menuBarParams, shapes3DParams, settings3D;
		ofXml settings;
        ofTrueTypeFont font;
        ofxButton *importButton, *exportButton, *mergeButton, *unmergeButton, *next, *unselect;
		//ofxButton *lineButton, *triangleButton, *rectangleButton, *circleButton;

		// *
		RendererModel *rendererModel;
		bool showGui; // boolean variable utilized for show/hide interface
        bool hideCamera; // boolean used to hide all panels not usefull for the camera mode.
        string s; // string to explain how camera works.
};
