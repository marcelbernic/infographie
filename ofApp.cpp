#include "ofApp.h"
#include <ostream>

ofApp::ofApp()
{
	renderer2d = nullptr;
	rendererModel = nullptr;
    renderer3d = nullptr;
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetWindowTitle("Paint3D+");

    m_firstTimeSelection = 1;
	renderer2d = new Renderer2D();
	renderer2d->setup("2D", this);

    renderer3d = new Renderer3D();
    renderer3d->setup("3D", this);

	rendererModel = new RendererModel(); //*

	//Panels params
	menuBarParams.setName("Menu");
	menuBarParams.add(b2D.set("2D", true));
	menuBarParams.add(b3D.set("3D", false));
	menuBarParams.add(bModelMode.set("Model Mode", false)); //*
	importButton = new ofxButton();
	exportButton = new ofxButton();
	mergeButton = new ofxButton();
	unmergeButton = new ofxButton();
    next = new ofxButton();
    unselect = new ofxButton();

    shapesParams.setName("2D Shapes");
	shapesParams.add(bLine.set("Line", false));
	shapesParams.add(bTriangle.set("Triangle", false));
	shapesParams.add(bRectangle.set("Rectangle", false));
	shapesParams.add(bCircle.set("Circle", false));

    shapes3DParams.setName("3D Shapes");
    shapes3DParams.add(bCube.set("Cube", false));
    shapes3DParams.add(bSphere.set("Sphere", false));

	shapesSettingsParams.setName("2D Settings");
	shapesSettingsParams.add(vSync.set("vSync",true));
	shapesSettingsParams.add(renderer2d->parameters);

	importButton->setup("Import");
	exportButton->setup("Export");
	mergeButton->setup("Merge Shapes");
	unmergeButton->setup("Unmerge Shapes");
    next->setup("Select next 3D shape");
    unselect->setup("Unselect");

	//Setup panels
	menuPanel.setup(menuBarParams);
	menuPanel.add(importButton);
	menuPanel.add(exportButton);
	menuPanel.add(bSelect.set("Selection", false));
	shapesPanel.setup(shapesParams);
	shapesPanel.add(mergeButton);
	shapesPanel.add(unmergeButton);
    shapesParamsPanel.setup(shapesSettingsParams);
    shapes3DPanel.setup(shapes3DParams);
    shapes3DPanel.add(next);
    shapes3DPanel.add(unselect);
    shapes3DPanel.add(renderer3d->parameters3D);
	menuPanel.setPosition(0, 0);
	shapesPanel.setPosition(0, 5 + menuPanel.getHeight());
	shapesParamsPanel.setPosition(0, 5 + shapesPanel.getHeight() + menuPanel.getHeight());
    shapes3DPanel.setPosition(205, 0);

	//Listeners
	b2D.addListener(this, &ofApp::b2DChanged);
	b3D.addListener(this, &ofApp::b3DChanged);
	bModelMode.addListener(this, &ofApp::bModelModeChanged); //*
	importButton->addListener(this, &ofApp::buttonPressed);
	exportButton->addListener(this, &ofApp::buttonPressed);
	mergeButton->addListener(this, &ofApp::buttonPressed);
	unmergeButton->addListener(this, &ofApp::buttonPressed);
    next->addListener(this, &ofApp::buttonPressed);
    unselect->addListener(this, &ofApp::buttonPressed);
	bLine.addListener(this, &ofApp::bLineChanged);
	bTriangle.addListener(this, &ofApp::bTriangleChanged);
	bRectangle.addListener(this, &ofApp::bRectangleChanged);
	bCircle.addListener(this, &ofApp::bCircleChanged);
	bSelect.addListener(this, &ofApp::bSelectChanged);
    bCube.addListener(this, &ofApp::bCubeChanged);
    bSphere.addListener(this, &ofApp::bSphereChanged);

    //gui.loadFromFile("settings.xml");

    font.load(OF_TTF_SANS, 10, true, true);
    ofEnableAlphaBlending();

	//Default Parameters
	m_state = AppState::ACTION_SELECT;
	m_mode = MODE_2D;
	m_clickRadius = 5;
	isTakingScreenshot = false;
	isClearingButtonsShapes = false;
	isClearingButtonsModes = false;
    m_selectionIndex = 0;

	showGui = true;
	ofSetLogLevel(OF_LOG_VERBOSE);
}

void ofApp::b2DChanged(bool & p_2D) {
	if (!isClearingButtonsModes) {
		isClearingButtonsModes = true;
        b3D.set(false);
		bModelMode.set(false); //*
        b2D.set(p_2D);
		isClearingButtonsModes = false;
		m_mode = MODE_2D;
		showGui = true; //*
	}
}

void ofApp::b3DChanged(bool & p_3D) {
	if (!isClearingButtonsModes) {
		isClearingButtonsModes = true;
        b2D.set(false);
		bModelMode.set(false); //*
        b3D.set(p_3D);
		isClearingButtonsModes = false;
		m_mode = MODE_3D;
		showGui = true; //*
	}
}

void ofApp::bModelModeChanged(bool & p_modelMode) { //*
	if (!isClearingButtonsModes) {
		isClearingButtonsModes = true;
		b2D.set(false);
		b3D.set(false);
		bModelMode.set(true);
		isClearingButtonsModes = false;
		m_mode = MODE_MODEL;
		showGui = false;
	}
}

void ofApp::vSyncChanged(bool & vSync){
	ofSetVerticalSync(vSync);
}

void ofApp::bLineChanged(bool & pLine) {
	if (!isClearingButtonsShapes) {
        b3D.set(false);
        b2D.set(true);
		clearButtons();
		isClearingButtonsShapes = false;
		bLine.set(true);
		m_buffer.clear();
		m_state = AppState::BUILD_LINE;
	}
}
void ofApp::bTriangleChanged(bool & pTriangle) {
	if (!isClearingButtonsShapes) {
		clearButtons();
		isClearingButtonsShapes = false;
		bTriangle.set(true);
        b3D.set(false);
        b2D.set(true);
		m_buffer.clear();
		m_state = AppState::BUILD_TRIANGLE;
	}
}
void ofApp::bRectangleChanged(bool & pRectangle) {
	if (!isClearingButtonsShapes) {
		clearButtons();
		isClearingButtonsShapes = false;
		bRectangle.set(true);
        b3D.set(false);
        b2D.set(true);
		m_buffer.clear();
		m_state = AppState::BUILD_RECTANGLE;
	}
}
void ofApp::bCircleChanged(bool & pCircle) {
	if (!isClearingButtonsShapes) {
		clearButtons();
		isClearingButtonsShapes = false;
		bCircle.set(true);
        b3D.set(false);
        b2D.set(true);
		m_buffer.clear();
		m_state = AppState::BUILD_CIRCLE;
	}
}
void ofApp::bSelectChanged(bool & pSelect) {
	if (!isClearingButtonsShapes) {
		clearButtons();
		isClearingButtonsShapes = false;
		bSelect.set(true);
		m_buffer.clear();
		m_state = AppState::ACTION_SELECT;
	}
}

void ofApp::bCubeChanged(bool & p_cube) {
    if (!isClearingButtonsShapes) {
        clearButtons();
        isClearingButtonsShapes = false;
        bCube.set(true);
        b2D.set(false);
        b3D.set(true);
        m_buffer.clear();
        m_state = AppState::BUILD_CUBE;
    }
}

void ofApp::bSphereChanged(bool & p_sphere) {
    if (!isClearingButtonsShapes) {
        clearButtons();
        isClearingButtonsShapes = false;
        bSphere.set(true);
        b2D.set(false);
        b3D.set(true);
        m_buffer.clear();
        m_state = AppState::BUILD_SPHERE;
    }
}


void ofApp::clearButtons() {
	isClearingButtonsShapes = true;
	bSelect.set(false);
	bLine.set(false);
	bTriangle.set(false);
	bRectangle.set(false);
	bCircle.set(false);
    bCube.set(false);
    bSphere.set(false);
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
	font.drawString("fps: " + ofToString((int)ofGetFrameRate()), ofGetWidth() - 150, 0);

	if (m_mode == MODE_2D) {
		renderer2d->draw();
	}
	else if (m_mode == MODE_MODEL) {
		rendererModel->draw();
	}
	else {
        renderer3d->draw();	}

	ofSetColor(255);
	if (!isTakingScreenshot) {
		menuPanel.draw();
		if (showGui) shapesPanel.draw();
		if (showGui) shapesParamsPanel.draw();
		if (showGui)  shapes3DPanel.draw();
	}

	drawCursor();
}

void ofApp::drawCursor() {
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	if (mouseIsOverPanel()) {
		ofShowCursor();
		return;
	}

	ofHideCursor();
	ofSetColor(0);
	ofSetLineWidth(4);
	ofNoFill();
	switch (m_state) {
	case AppState::ACTION_SELECT:
	case AppState::ACTION_GROUPSELECT:
		ofShowCursor();
		break;
	case AppState::BUILD_RECTANGLE:
		ofDrawRectangle(mouseX, mouseY, 16, 16);
		break;
	case AppState::BUILD_TRIANGLE:
		ofDrawTriangle(mouseX, mouseY, mouseX + 16, mouseY, mouseX, mouseY + 16);
		ofFill();
		ofDrawCircle(mouseX, mouseY, 2);
		ofDrawCircle(mouseX + 16, mouseY, 2);
		ofDrawCircle(mouseX, mouseY + 16, 2);
		break;
	case AppState::BUILD_CIRCLE:
		ofCircle(mouseX + 6, mouseY + 6, 8);
		break;
	case AppState::BUILD_LINE:
		ofDrawLine(mouseX, mouseY, mouseX + 16, mouseY + 16);
		break;
	case AppState::ACTION_TRANSLATE:
		ofSetLineWidth(2);
		ofDrawArrow(ofVec3f(mouseX + 8, mouseY + 8), ofVec3f(mouseX, mouseY + 8), 2);
		ofDrawArrow(ofVec3f(mouseX + 8, mouseY + 8), ofVec3f(mouseX + 16, mouseY + 8), 2);
		ofDrawArrow(ofVec3f(mouseX + 8, mouseY + 8), ofVec3f(mouseX + 8, mouseY), 2);
		ofDrawArrow(ofVec3f(mouseX + 8, mouseY + 8), ofVec3f(mouseX + 8, mouseY + 16), 2);
		break;
	case AppState::ACTION_ROTATE:
		ofDrawBezier(mouseX, mouseY, mouseX + 8, mouseY + 2, mouseX + 14, mouseY + 8, mouseX + 16, mouseY + 16);
		break;
	case AppState::ACTION_RESIZE:
		ofSetLineWidth(2);
		ofDrawArrow(ofVec3f(mouseX + 4, mouseY + 4), ofVec3f(mouseX, mouseY), 2);
		ofDrawArrow(ofVec3f(mouseX + 12, mouseY + 12), ofVec3f(mouseX + 16, mouseY + 16), 2);
		ofDrawRectangle(mouseX + 4, mouseY + 4, 8, 8);
		break;
	default:
		ofShowCursor();
		break;
	}
	ofFill();
}

bool ofApp::mouseIsOverPanel() {
	int mouseX = ofGetMouseX();
	int mouseY = ofGetMouseY();

	if ((menuPanel.getPosition().x <= mouseX) && (mouseX <= (menuPanel.getPosition().x + menuPanel.getWidth()))
		&& (menuPanel.getPosition().y <= mouseY) && (mouseY <= (menuPanel.getPosition().y + menuPanel.getHeight()))) {
		return true;
	}

	else if ((shapesPanel.getPosition().x <= mouseX) && (mouseX <= (shapesPanel.getPosition().x + shapesPanel.getWidth()))
		&& (shapesPanel.getPosition().y <= mouseY) && (mouseY <= (shapesPanel.getPosition().y + shapesPanel.getHeight()))) {
		return true;
	}

	else if ((shapesParamsPanel.getPosition().x <= mouseX) && (mouseX <= (shapesParamsPanel.getPosition().x + shapesParamsPanel.getWidth()))
		&& (shapesParamsPanel.getPosition().y <= mouseY) && (mouseY <= (shapesParamsPanel.getPosition().y + shapesParamsPanel.getHeight()))) {
		return true;
	}
	else if ((shapes3DPanel.getPosition().x <= mouseX) && (mouseX <= (shapes3DPanel.getPosition().x + shapes3DPanel.getWidth()))
		&& (shapes3DPanel.getPosition().y <= mouseY) && (mouseY <= (shapes3DPanel.getPosition().y + shapes3DPanel.getHeight()))) {
		return true;
	}

	else if ((shapes3DParamsPanel.getPosition().x <= mouseX) && (mouseX <= (shapes3DParamsPanel.getPosition().x + shapes3DParamsPanel.getWidth()))
		&& (shapes3DParamsPanel.getPosition().y <= mouseY) && (mouseY <= (shapes3DParamsPanel.getPosition().y + shapes3DParamsPanel.getHeight()))) {
		return true;
	}

	return false;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (m_mode == MODE_2D) {
		if (ofGetKeyPressed(OF_KEY_DEL)) {
			deleteSelection();
			m_buffer.clear();
		}

		if (key == '+') {
			for (Obj2D* o : m_obj2DVector) {
				o->resize(2);
			}
			m_buffer.clear();
		}
		if (key == '-') {
			for (Obj2D* o : m_obj2DVector) {
				o->resize(0.5);
			}
			m_buffer.clear();
		}
	}
	else if (m_mode == MODE_MODEL) { //*
		if (ofGetKeyPressed('l')) {
			rendererModel->switchLight = !rendererModel->switchLight;
		}
		if (ofGetKeyPressed('m')) {
			rendererModel->switchMaterials = !rendererModel->switchMaterials;
			if (rendererModel->switchMaterials) rendererModel->model.disableMaterials();
			if (!rendererModel->switchMaterials) rendererModel->model.enableMaterials();
		}
		if (ofGetKeyPressed('t')) {
			rendererModel->switchTextures = !rendererModel->switchTextures;
			if (rendererModel->switchTextures) rendererModel->model.disableTextures();
			if (!rendererModel->switchTextures) rendererModel->model.enableTextures();
		}
	}
	else {
		//3D
	}
}

void ofApp::deleteSelection() {
	int size = m_obj2DVector.size();
	for (int i = 0; i < m_obj2DVector.size(); i++) {
		if (m_obj2DVector[i]->isSelected()) {
			//DELETE OBJ
			m_obj2DVector.erase(m_obj2DVector.begin() + i);
			i--;
			size--;
		}
	}
}

void ofApp::buttonPressed(const void * sender){
    ofxButton * button = (ofxButton*)sender;
	string btnName = button->getName();

	if (m_mode == MODE_2D) {
		if (btnName == "Import") {
			ofFileDialogResult file = ofSystemLoadDialog("Load Image", false);
			if (file.getPath() != "") {
				app::Image2D *newImage = new app::Image2D(file.getPath(), 64, 64, Coord(ofGetWidth() / 2, ofGetHeight() / 2), 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get());
				if (newImage->getImage().getTextureReference().isAllocated()) {
					m_obj2DVector.push_back(newImage);
				}
			}
		}

		else if (btnName == "Export") {
			isTakingScreenshot = true;
			draw();
			isTakingScreenshot = false;

			ofFileDialogResult file = ofSystemSaveDialog("Save", "Export");

			if (file.getPath() != "") {
				renderer2d->imageExport(file.getPath(), "png");
			}
		}

		else if (btnName == "Merge Shapes") {
			std::vector<Obj2D*> glued;
			int size = m_obj2DVector.size();
			for (int i = 0; i < m_obj2DVector.size(); i++) {
				if (m_obj2DVector[i]->isSelected()) {
					glued.push_back(m_obj2DVector[i]);
					m_obj2DVector.erase(m_obj2DVector.begin() + i);
					i--;
					size--;
				}
			}
			m_obj2DVector.push_back(new app::Obj2DCollection(glued));
			m_obj2DVector.back()->setSelected(true);
			cout << "Created" << endl;
			m_buffer.clear();
		}

		else if (btnName == "Unmerge Shapes") {
			std::vector<Obj2D*> glued;
			int size = m_obj2DVector.size();
			for (int i = 0; i < m_obj2DVector.size(); i++) {
				if (m_obj2DVector[i]->getType() == EnumVectorDrawMode::VECTOR_PRIMITIVE_COLLECTION && m_obj2DVector[i]->isSelected()) {
					app::Obj2DCollection* j = dynamic_cast<app::Obj2DCollection*>(m_obj2DVector[i]);
					for (Obj2D* o : getCollectionObjects(j)) {
						glued.push_back(o);
					}
					m_obj2DVector.erase(m_obj2DVector.begin() + i);
					i--;
					size--;
				}
			}
			for (Obj2D* o : glued) {
				m_obj2DVector.push_back(o);
			}
			m_buffer.clear();
		}
	}
	else if (m_mode == MODE_MODEL) { //*
		if (btnName == "Import") {
			ofFileDialogResult file = ofSystemLoadDialog("Select a model file to load");
			if (file.bSuccess) {
				rendererModel->processOpenFileSelection(file);
			}
		}
	}
	else {
		//3D
        if (btnName == "Select next 3D shape") {
            if(m_obj3DVector.size() > 0){

                if (m_firstTimeSelection == 1){
                    m_firstTimeSelection = 0;
                    m_selectionIndex = 0;
                    m_obj3DVector[m_selectionIndex]->setSelected(false);
                    m_selectionIndex = m_selectionIndex % m_obj3DVector.size();
                    m_obj3DVector[m_selectionIndex]->setSelected(true);
                    renderer3d->bCloud.set(m_obj3DVector[m_selectionIndex]->isCloud());
                }
                else{
                    m_obj3DVector[m_selectionIndex]->setSelected(false);
                    m_selectionIndex = (m_selectionIndex + 1) % m_obj3DVector.size();
                    m_obj3DVector[m_selectionIndex]->setSelected(true);
                    renderer3d->bCloud.set(m_obj3DVector[m_selectionIndex]->isCloud());
                }
            }
        }
        else if (btnName == "Unselect") {
            if(m_firstTimeSelection == 0){
                m_obj3DVector[m_selectionIndex]->setSelected(false);

            }
        }

	}	
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (m_mode == MODE_2D) {
		if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT) && ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
			switch (m_state) {
			case AppState::ACTION_SELECT:
			case AppState::ACTION_TRANSLATE:
			case AppState::ACTION_GROUPSELECT:
				m_buffer.clear();
				m_buffer.push_back(Coord(x, y));
				m_buffer.push_back(Coord(x, y));
				m_state = AppState::ACTION_ROTATE;
				break;
			case AppState::ACTION_ROTATE:
				m_buffer[0] = m_buffer[1];
				m_buffer[1].setX(x);
				m_buffer[1].setY(y);
				rotateSelection();
				break;
			}
		}
		else if (button == OF_MOUSE_BUTTON_LEFT) {
			switch (m_state) {
			case AppState::ACTION_SELECT:
				m_buffer.clear();
				m_buffer.push_back(Coord(x, y));
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
		else if (button == OF_MOUSE_BUTTON_RIGHT &&
				(ofGetKeyPressed(OF_KEY_LEFT_CONTROL) || ofGetKeyPressed(OF_KEY_RIGHT_CONTROL))) {
			switch (m_state) {
			case AppState::ACTION_SELECT:
				m_buffer.clear();
				m_buffer.push_back(Coord(x, y));
				m_buffer.push_back(Coord(x, y));
				m_state = AppState::ACTION_RESIZE;
				break;
			case AppState::ACTION_RESIZE:
				m_buffer[0] = m_buffer[1];
				m_buffer[1].setX(x);
				m_buffer[1].setY(y);
				resizeSelection();
				break;
			}
		}
		else if (button == OF_MOUSE_BUTTON_RIGHT) {
			switch (m_state) {
			case AppState::ACTION_SELECT:
				m_buffer.clear();
				m_buffer.push_back(Coord(x, y));
				m_buffer.push_back(Coord(x, y));
				m_state = AppState::ACTION_TRANSLATE;
				break;
			case AppState::ACTION_TRANSLATE:
				m_buffer[0] = m_buffer[1];
				m_buffer[1].setX(x);
				m_buffer[1].setY(y);
				translateSelection(m_buffer[1].getX() - m_buffer[0].getX(), m_buffer[1].getY() - m_buffer[0].getY());
				break;
			}
		}
	}
	else {
		//3D
	}
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	bool isMouseOnPanels = mouseIsOverPanel();
	if (m_mode == MODE_2D && !isMouseOnPanels) {
		if (button == OF_MOUSE_BUTTON_LEFT) {
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
				if (!(ofGetKeyPressed(OF_KEY_LEFT_CONTROL) || ofGetKeyPressed(OF_KEY_RIGHT_CONTROL))) {
					clearSelected();
				}
				for (Obj2D* o : m_obj2DVector) {
					if (o->checkSelected(Coord(x, y), m_clickRadius)) {
						break;
					}
				}
				break;
			}
		}
		else if (button == OF_MOUSE_BUTTON_RIGHT) {
			switch (m_state) {
			case AppState::ACTION_SELECT:
				m_buffer.clear();
				m_buffer.push_back(Coord(x, y));
			}
		}
	}
	else if (m_mode == MODE_3D && !isMouseOnPanels) {
		//3D
        if (button == OF_MOUSE_BUTTON_LEFT) {
            switch (m_state) {
            case AppState::BUILD_CUBE:
                m_buffer3D.push_back(Coord3D(x, y, m_obj3DVector.size() + 30));
                if (m_buffer3D.size() == 1) {
                    buildCube();
                    m_buffer3D.clear();
                }
                break;
            case AppState::BUILD_SPHERE:
                m_buffer3D.push_back(Coord3D(x, y, m_obj3DVector.size() + 30));
                if (m_buffer3D.size() == 1) {
                    buildSphere();
                    m_buffer3D.clear();
                }
                break;

            }
        }
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (m_mode == MODE_2D) {
		if (button == OF_MOUSE_BUTTON_LEFT) {
			switch (m_state) {
			case AppState::ACTION_ROTATE:
			case AppState::ACTION_GROUPSELECT:
				m_buffer.clear();
				m_state = AppState::ACTION_SELECT;
				break;
			}
		}
		else if (button == OF_MOUSE_BUTTON_RIGHT) {
			switch (m_state) {
			case AppState::ACTION_ROTATE:
			case AppState::ACTION_RESIZE:
			case AppState::ACTION_TRANSLATE:
				m_buffer.clear();
				m_state = AppState::ACTION_SELECT;
				break;
			}
		}
	}
	else {
		//3D
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
		m_obj2DVector.push_back(new app::Rectangle(m_buffer[0], width, height, 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
	}
	else if (width < 0 && height >= 0) { //0 = top-right, 1 = bottom-left
		m_obj2DVector.push_back(new app::Rectangle(Coord(m_buffer[1].getX(), m_buffer[0].getY()), -width, height, 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
	}
	else if (width >= 0 && height < 0) { //0 = bottom-left, 1 = top-right
		m_obj2DVector.push_back(new app::Rectangle(Coord(m_buffer[0].getX(), m_buffer[1].getY()), width, -height, 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
	}
	else { //0 = bottom-right, 1 = top-left
		m_obj2DVector.push_back(new app::Rectangle(m_buffer[1], -width, -height, 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
	}
}

void ofApp::buildTriangle() {
	m_obj2DVector.push_back(new app::Triangle(m_buffer, 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
}

void ofApp::buildCircle() {
	double radius = calculateDistance(m_buffer[0], m_buffer[1]);
	m_obj2DVector.push_back(new app::Circle(m_buffer[0], radius, 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
}

void ofApp::buildLine() {
	m_obj2DVector.push_back(new app::Line2D(m_buffer, 0, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorStroke.get()));
}

void ofApp::buildCube() {
    m_obj3DVector.push_back(new app::Cube3D(m_buffer3D, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
}

void ofApp::buildSphere() {
    m_obj3DVector.push_back(new app::Sphere3D(m_buffer3D, renderer2d->strokeWidth.get(), renderer2d->colorStroke.get(), renderer2d->colorSelected.get(), renderer2d->colorFill.get()));
}

double ofApp::calculateDistance(Coord p_coord1, Coord p_coord2) {
	double x2 = pow((p_coord1.getX() - p_coord2.getX()), 2);
	double y2 = pow((p_coord1.getY() - p_coord2.getY()), 2);
	return sqrt(x2 + y2);
}

void ofApp::clearSelected() {
	for (Obj2D* o : m_obj2DVector) {
		o->setSelected(false);
	}
}

void ofApp::updateGroupSelection() {
	double width = m_buffer[1].getX() - m_buffer[0].getX();
	double height = m_buffer[1].getY() - m_buffer[0].getY();
	Coord topLeft = Coord(0,0);
	if (width >= 0 && height >= 0) { //0 = top-left, 1 = bottom-right
		topLeft = m_buffer[0];
		//cout << "TOP-LEFT" << endl;
	}
	else if (width < 0 && height >= 0) { //0 = top-right, 1 = bottom-left
		topLeft = Coord(m_buffer[1].getX(), m_buffer[0].getY());
		//cout << "TOP-RIGHT" << endl;
	}
	else if (width >= 0 && height < 0) { //0 = bottom-left, 1 = top-right
		topLeft = Coord(m_buffer[0].getX(), m_buffer[1].getY());
		//cout << "BOTTOM-LEFT" << endl;
	}
	else { //0 = bottom-right, 1 = top-left
		topLeft = m_buffer[1];
		//cout << "BOTTOM-RIGHT" << endl;
	}
	for (Obj2D* o : m_obj2DVector) {
		o->setSelected(o->containedInRect(topLeft, abs(width), abs(height)));
	}
}

void ofApp::translateSelection(double p_x, double p_y) {
	for (Obj2D* o : m_obj2DVector) {
		if (o->isSelected()) {
			o->translate(p_x, p_y);
		}
	}
}

void ofApp::rotateSelection() {
	cout << "rotate" << endl;
	for (Obj2D* o : m_obj2DVector) {
		if (o->isSelected()) {
			o->rotate(m_buffer[0], m_buffer[1]);
		}
	}
}

void ofApp::resizeSelection() {
	for (Obj2D* o : m_obj2DVector) {
		if (o->isSelected()) {
			o->resize(calculateDistance(m_buffer[1], o->getRotationCenter()) / calculateDistance(m_buffer[0], o->getRotationCenter()));
		}
	}
}

std::vector<Obj2D*> ofApp::getCollectionObjects(app::Obj2DCollection* p_coll) {
	return p_coll->getObjVector();
}

void ofApp::exit()
{
	ofLog() << "<ofApp::exit>";
}

void ofApp::clear2DButtons(){
    bLine.set(false);
    bTriangle.set(false);
    bRectangle.set(false);
    bCircle.set(false);
}

void ofApp::clear3DButtons(){
    bCube.set(false);
    renderer3d->bCloud.set(false);
}

ofApp::~ofApp()
{
	if (nullptr != renderer2d)
		delete renderer2d;
	if (nullptr != rendererModel) //*
		delete rendererModel; //*
	
}
