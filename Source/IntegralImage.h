#ifndef _INTEGRAL_IMAGE_H_
#define _INTEGRAL_IMAGE_H_

#include "TypeDef.h"

class IntegralImage
{
private:
	UInt *values;
	UInt *values2;
	UInt stride;

	void calcFromPicture(unsigned char* picture);

public:

	IntegralImage(UInt width, UInt height, UInt *picture);
	~IntegralImage();

	UInt width;
	UInt height;
	
	UInt getSumInRect(UInt top, UInt left, UInt width, UInt height);
	UInt getSum2InRect(UInt top, UInt left, UInt width, UInt height);
};

#endif