// IFT3100H16_HelloTriangle/ofApp.h
// Classe principale de l'application.

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:

    float vertex1_X;
    float vertex1_Y;
    float vertex2_X;
    float vertex2_Y;
    float vertex3_X;
    float vertex3_Y;

    float pointRadius;

    void setup();
    void update();
    void draw();
    void exit();
};
