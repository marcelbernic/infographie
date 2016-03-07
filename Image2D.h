#pragma once
#include "Obj2D.h"
class Image2D :
	public Obj2D
{
public:
	Image2D();

	void importImage();
	void exportImage();

	~Image2D();
};

