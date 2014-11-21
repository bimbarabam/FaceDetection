#include "HaarArea.h"


void HaarArea::setScaleAndWeight(double scale, double weight)
{
	if (this->numRectangles == 2)
	{
		HaarRectangle a = rectangles[0];
		HaarRectangle b = rectangles[1];

		rectangles[0]->scaleSize(scale);
		rectangles[0]->scaleWeight(weight);

		rectangles[1]->scaleSize(scale);
		rectangles[1]->scaleWeight(-(rectangles[1]->scaledArea() * rectangles[1]->scaledWeight()) / rectangles[0]->scaledArea());
	}
	else // this->numRectangles == 3
	{
		rectangles[2]->scaleSize(scale);
		rectangles[2]->scaleWeight(weight);

		rectangles[1]->scaleSize(scale);
		rectangles[1]->scaleWeight(weight);

		rectangles[0]->scaleSize(scale);
		rectangles[0]->scaleWeight = -(rectangles[1]->scaledArea() * rectangles[1]->scaledWeight()
			+ rectangles[2]->scaledArea() * rectangles[2]->scaledWeight()) / (rectangles[0]->scaledArea());
	}
}

double HaarArea::checkMatch(IntegralImage* image, UInt top, UInt left, double scaleFactor)
{
	double sum = 0.0;

	for (int i = 0; i < this->numRectangles; ++i)
	{
		HaarRectangle* rect = this->rectangles[i];
		sum += image->getSumInRect(left + rect->scaledX(), top + rect->scaledY(),
			rect->scaledWidth(), rect->scaledHeight()) * rect->scaledWeight();
	}
}
