#include "pch.h"
#include "cpoint3d.h"

CPoint3D::CPoint3D()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

CPoint3D::CPoint3D(int xPos, int yPos, int zPos)
{
	this->x = xPos;
	this->y = yPos;
	this->z = zPos;
}
