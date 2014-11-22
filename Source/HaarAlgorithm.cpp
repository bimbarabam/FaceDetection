#include "HaarAlgorithm.h"
#include "HaarArea.h"
#include "Stage.h"
#include <algorithm>
#include <math.h>

void HaarAlgorithm::generateFaceStages()
{
	stages = new Stage[STAGES_COUNT];
	
	stages[0].threshold = 0.822689414024353;
	HaarRectangle r1(3, 7, 14, 4, -1), r2(3, 9, 14, 2, 2);
	HaarRectangle r3(1, 2, 18, 4, -1), r4(7, 2, 6, 4, 3);
	HaarRectangle r5(1, 7, 15, 9, -1), r6(1, 10, 15, 3, 3);
	stages[0].haarAreas = new HaarArea*[3];
	stages[0].numAreas = 3;
	stages[0].haarAreas[0] = new HaarArea(0.004014195874333382, 0.0337941907346249, 0.8378106951713562, r1, r2);
	stages[0].haarAreas[1] = new HaarArea(0.0151513395830989, 0.1514132022857666, 0.7488812208175659, r3, r4);
	stages[0].haarAreas[2] = new HaarArea(0.004210993181914091, 0.0900492817163467, 0.6374819874763489, r5, r6);
}

std::vector<HaarRectangle> HaarAlgorithm::execute(IntegralImage* image)
{
	float stopScale = std::min(image->width / (float)BASE_CLASSIFIER_SIZE, image->height / (float)BASE_CLASSIFIER_SIZE);
	float currentScale = 1.0f;
	bool end = false;

	std::vector<HaarRectangle> result;

	HaarRectangle window;

	do
	{
		float invArea = 1.0f / (BASE_CLASSIFIER_SIZE * BASE_CLASSIFIER_SIZE * currentScale * currentScale);

		for (int i = 0; i < STAGES_COUNT; ++i)
		{
			Stage& stage = stages[i];
			for (UInt j = 0; j < stage.numAreas; ++j)
			{
				HaarArea* area = stage.haarAreas[j];
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

	return result;
}

bool HaarAlgorithm::searchWindow(IntegralImage* image, HaarRectangle window, float invArea)
{
	double mean = image->getSumInRect(window.left, window.top, window.width, window.height) * invArea;
	double factor = image->getSum2InRect(window.left, window.top, window.width, window.height) * invArea - (mean * mean);

	factor = (factor >= 0) ? std::sqrt(factor) : 1;

	for (int i = 0; i < STAGES_COUNT; ++i)
	{
		if (stages[i].check(image, window.top, window.left, factor) == false)
		{
			return false;
		}
	}

	return true;
}

