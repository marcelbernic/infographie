#pragma once
#include "Obj2D.h"
namespace app {
class Obj2DCollection : public Obj2D
{
private:
	std::vector<Obj2D*> m_objVector;
public:
	Obj2DCollection(std::vector<Obj2D*> p_objVector);
	~Obj2DCollection();

	std::vector<Obj2D*> getObjVector();
	void resize(Coord p_coord, double p_percent) override;
	void setSelected(bool p_selected);
	bool checkSelected(Coord p_clickPoint, double p_radius) override;
	bool checkCollision(Coord p_clickPoint, double p_radius);
	bool Obj2DCollection::containedInRect(Coord p_topLeft, double p_width, double p_height);
	void rotate(Coord p_coord, double p_degree) override;
	void translate(double p_x, double p_y) override;
};
}
