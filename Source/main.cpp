#include <cstdio>
#include <stdio.h>

#include "imgIO.hpp"

int main( )
{
	const char* pathIn       = "1.jpg";
	const char* pathOutGrey  = "obrazTestOutGrey.jpg";
	const char* pathOutColor = "obrazTestOutColor.jpg";

	unsigned char *imgColor = NULL;
	unsigned char *imgGrey  = NULL;
	
	ImgIO imgIO;

	imgIO.ReadImgColor ( pathIn, imgColor  );
	
	imgIO.ColorToGray( imgColor, imgGrey );
	
	imgIO.WriteImgColor( pathOutColor, imgColor );
	imgIO.WriteImgGrey ( pathOutGrey , imgGrey  );

	delete[] imgColor;
	delete[] imgGrey;

	return 0;
}