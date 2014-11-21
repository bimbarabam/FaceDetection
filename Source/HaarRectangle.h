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
		sizeScale(1f),
		weightScale(1f)
	{

	}

	HaarRectangle() :
		top(0),
		left(0),
		width(0),
		height(0),
		weight(0f),
		sizeScale(1.0f),
		weightScale(1f)
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
	~HaarRectangle();

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
		return this->left * sizeScale;
	}
	UInt scaledY()
	{
		return this->top * sizeScale;
	}
	UInt scaledWidth()
	{
		return this->width * sizeScale;
	}
	UInt scaledHeight()
	{
		return this->height * sizeScale;
	}
	UInt scaledArea()
	{
		return scaledWidth() * scaledHeight();
	}
	float scaledWeight()
	{
		return weight * weightScale;
	}
};

#endif