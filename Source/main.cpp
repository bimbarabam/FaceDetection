#include <cstdio>
#include <stdio.h>
#include "HaarAlgorithm.h"
#include "IntegralImage.h"
#include "imgIO.hpp"

int main( )
{
	const char* pathIn       = "judybats.jpg";
	const char* pathOutGrey  = "obrazTestOutGrey.jpg";
	const char* pathOutColor = "obrazTestOutColor.jpg";

	unsigned char *imgColor = NULL;
	unsigned char *imgGrey = NULL;
	unsigned char *transposed = NULL;
	
	ImgIO imgIO;

	imgIO.ReadImgColor ( pathIn, imgColor  );
	
	imgIO.ColorToRed(imgColor, imgGrey);
	//imgIO.Transpose(imgGrey, transposed);

	IntegralImage image(imgIO.getSizeX(), imgIO.getSizeY(), imgGrey);
	HaarAlgorithm alg;
	alg.execute(&image);
	
	imgIO.WriteImgColor( pathOutColor, imgColor );
	imgIO.WriteImgGrey ( pathOutGrey , imgGrey  );

	delete[] imgColor;
	delete[] imgGrey;
	delete[] transposed;

	return 0;
}