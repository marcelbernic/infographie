// IFT3100H16_HelloTriangle/ofApp.cpp
// Classe principale de l'application.

#include "ofApp.h"

// fonction invoquée à l'initialisation de l'application
void ofApp::setup()
{
    ofSetWindowTitle("HelloTriangle");

    ofSetFrameRate(1);

    ofLog() << "<ofApp::setup>";

    pointRadius = 16;
}

// fonction invoquée lors d'une mise à jour de la logique de l'application
void ofApp::update()
{
    vertex1_X = ofRandom(0, ofGetWidth());
    vertex1_Y = ofRandom(0, ofGetHeight());
    vertex2_X = ofRandom(0, ofGetWidth());
    vertex2_Y = ofRandom(0, ofGetHeight());
    vertex3_X = ofRandom(0, ofGetWidth());
    vertex3_Y = ofRandom(0, ofGetHeight());

    ofLog() << setprecision(4) << "<triangle: v1:("
        << vertex1_X   << ", " << vertex1_Y << ") v2:("
        << vertex2_X   << ", " << vertex2_Y << ") v3:("
        << vertex3_X   << ", " << vertex3_Y << ")>";
}

// fonction invoquée lors d'une mise à jour du rendu de la fenêtre de l'application
void ofApp::draw()
{
    ofClear(191);

    ofFill();
    ofSetColor(255);

    ofDrawTriangle(
        vertex1_X, vertex1_Y,
        vertex2_X, vertex2_Y,
        vertex3_X, vertex3_Y);

    ofSetColor(0);

    ofDrawEllipse(vertex1_X, vertex1_Y, pointRadius, pointRadius);
    ofDrawEllipse(vertex2_X, vertex2_Y, pointRadius, pointRadius);
    ofDrawEllipse(vertex3_X, vertex3_Y, pointRadius, pointRadius);
}

// fonction invoquée quand l'application quitte
void ofApp::exit()
{
    ofLog() << "<ofApp::exit>";
}
