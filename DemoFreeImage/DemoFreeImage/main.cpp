#include <iostream>
#include "FreeImage.h"
#include "Vector3.h"

int main(int argc, char** argv)
{

	RGBQUAD color;
	FIBITMAP* image;
	image = FreeImage_Allocate(256, 256, 32);

	color.rgbGreen = 0;

	for (size_t i = 0; i < 640; i++)
	{
		color.rgbRed = static_cast<BYTE>(i);

		for (size_t j = 0; j < 480; j++)
		{
			color.rgbBlue = static_cast<BYTE>(j);

			FreeImage_SetPixelColor(image, i, j, &color);
		}
	}

	FreeImage_Save(FIF_BMP, image, "out.bmp");

	return EXIT_SUCCESS;

}