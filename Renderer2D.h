#pragma once

#include "ofMain.h"

class Renderer2D
{
public:
	Renderer2D();
	~Renderer2D();

	void setup();

	void draw();
	void drawZone(float x1, float y1, float x2, float y2) const;
	//void Renderer::drawCursor(float x, float y) const;

	void imageExport(const string name, const string extension) const;
};

