#ifndef _HAAR_RECTANGLE_H_
#define _HAAR_RECTANGLE_H_

#include "TypeDef.h"

class HaarRectangle
{
public:
	HaarRectangle(UInt top, UInt left, UInt width, UInt height, float weight) :
		top(top),
		left(left),
		width(width),
		height(height),
		weight(weight),
		sizeScale(1.0f),
		weightScale(1.0f)
	{

	}

	HaarRectangle() :
		top(0),
		left(0),
		width(0),
		height(0),
		weight(0.0f),
		sizeScale(1.0f),
		weightScale(1.0f)
	{

	}

	HaarRectangle(const HaarRectangle& rhs) :
		top(rhs.top),
		left(rhs.left),
		width(rhs.width),
		height(rhs.height),
		weight(rhs.weight),
		sizeScale(rhs.sizeScale),
		weightScale(rhs.weightScale)
	{

	}

	HaarRectangle& HaarRectangle::operator=(HaarRectangle rhs)
	{
		top = (rhs.top);
		left = (rhs.left);
		width = (rhs.width);
		height = (rhs.height);
		weight = (rhs.weight);
		sizeScale = (rhs.sizeScale);
		weightScale = rhs.weightScale;
		return *this;
	}
	~HaarRectangle()
	{

	}

	UInt top, left, width, height, bottom, right;

	float weight, sizeScale, weightScale;

	void scaleSize(float scale)
	{
		sizeScale = scale;
	}
	void scaleWeight(float scale)
	{
		weightScale = scale;
	}
	UInt scaledX()
	{
		return (UInt)(this->left * sizeScale);
	}
	UInt scaledY()
	{
		return (UInt)(this->top * sizeScale);
	}
	UInt scaledWidth()
	{
		return (UInt)(this->width * sizeScale);
	}
	UInt scaledHeight()
	{
		return (UInt)(this->height * sizeScale);
	}
	UInt scaledArea()
	{
		return (UInt)(scaledWidth() * scaledHeight());
	}
	float scaledWeight()
	{
		return weight * weightScale;
	}
};

#endif