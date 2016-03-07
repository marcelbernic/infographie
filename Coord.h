#pragma once
class Coord
{
private:
	double m_x;
	double m_y;

public:
	Coord(double p_x, double p_y);
	Coord(int p_x, int p_y);
	/*Coord(Coord p_coord);*/
	double getX();
	void setX(double p_x);
	void setX(int p_x);
	double getY();
	void setY(double p_y);
	void setY(int p_y);

	void addToX(double p_x);
	void addToX(int p_x);
	void addToY(double p_y);
	void addToY(int p_y);
	void addToCoord(Coord p_coord);

	~Coord();
};

