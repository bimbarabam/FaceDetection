#include "HaarAlgorithm.h"
#include <algorithm>
#include <math.h>

void HaarAlgorithm::generateFaceStages()
{

}

std::vector<HaarRectangle> HaarAlgorithm::execute(IntegralImage* image)
{
	float stopScale = std::min(image->width / (float)BASE_CLASSIFIER_SIZE, image->height / (float)BASE_CLASSIFIER_SIZE);
	float currentScale = 1f;
	bool end = false;

	std::vector<HaarRectangle> result;

	HaarRectangle window;

	do
	{
		float invArea = 1f / (BASE_CLASSIFIER_SIZE * BASE_CLASSIFIER_SIZE * currentScale * currentScale);

		for (int i = 0; i < STAGES_COUNT; ++i)
		{
			Stage* stage = stages[i];
			for (int j = 0; j < stage->numAreas; ++j)
			{
				HaarArea* area = stage->haarAreas[j];
				area->setScaleAndWeight(currentScale, invArea);
			}
		}

		window.width = (int)(BASE_CLASSIFIER_SIZE * currentScale);
		window.height = (int)(BASE_CLASSIFIER_SIZE * currentScale);

		int xStep = window.width >> WINDOW_STEP_SHIFT;
		int yStep = window.height >> WINDOW_STEP_SHIFT;

		int xEnd = image->width - window.width;
		int yEnd = image->height - window.height;

		for (int y = 0; y < yEnd; y += yStep)
		{
			window.top = y;

			for (int x = 0; x < xEnd; x += xStep)
			{
				window.left = x;

				if (searchWindow(image, window, invArea))
				{
					result.push_back(window);
				}
			}
		}

		currentScale *= SCALE_INCREASE;
	} while (currentScale <= stopScale);
}

bool HaarAlgorithm::searchWindow(IntegralImage* image, HaarRectangle window, float invArea)
{
	double mean = image->getSumInRect(window.left, window.top, window.width, window.height) * invArea;
	double factor = image.getSum2InRect(window.left, window.top, window.width, window.height) * invArea - (mean * mean);

	factor = (factor >= 0) ? std::sqrt(factor) : 1;

	for (int i = 0; i < STAGES_COUNT; ++i)
	{
		Stage* stage = stages[i];
		if (stage->check(image, window.top, window.left, factor) == false)
		{
			return false;
		}
	}

	return true;
}

