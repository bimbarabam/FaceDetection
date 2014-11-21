#ifndef _HAAR_AREA_H_
#define _HAAR_AREA_H_

#include "TypeDef.h"
#include "HaarRectangle.h"
#include "IntegralImage.h"

class HaarArea
{
private:
public:
	double threshold;
	double valueIfBigger;
	double valueIfSmaller;

	UInt numRectangles;
	HaarRectangle* rectangles;

	HaarArea(double threshold, double valueIfBigger, double valueIfSmaller, HaarRectangle rectangle1, HaarRectangle rectangle2);
	HaarArea(double threshold, double valueIfBigger, double valueIfSmaller, HaarRectangle rectangle1, HaarRectangle rectangle2, HaarRectangle rectangle3);
	~HaarArea();

	void setScaleAndWeight(double scale, double weight);
	double checkMatch(IntegralImage* image, UInt top, UInt left, double scaleFactor);
};

#endif