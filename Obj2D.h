#pragma once
#include "Coord.h"
#include "ofMath.h"

class Obj2D
{
private:

public:
	Obj2D();
	~Obj2D();

	void translate(double p_x, double p_y);
	void Obj2D::resize(double p_percent); // 1 = 100%
	void rotate(int p_degree);


	bool checkCollision(Coord p_clickPoint, double p_radius);
	double calculateDistance(Coord p_coord1, Coord p_coord2);
};

